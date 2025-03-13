#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>

// Convolution reverb includes
#include "/home/Cullen/FYP/Effects/Effects/include/TwoStageFFTConvolver.h"
#include "/home/Cullen/FYP/Effects/Effects/include/Utilities.h"
#include "/home/Cullen/FYP/Effects/Effects/include/WavFile.h"

// Include the Faust-generated algorithmic reverb code
// Make sure "algorithmicReverb.cpp" is in the same folder or adjust the path
#include "/home/Cullen/FYP/Effects/Effects/faust_programs/algorithmicReverb.cpp"

///////////////////////////////////////////////////////////////////////////////
// Data structure to hold all audio processing data
///////////////////////////////////////////////////////////////////////////////
struct MyAudioData 
{
    // Convolution reverb
    fftconvolver::TwoStageFFTConvolver convolver;
    size_t blockSize;
    std::vector<float> convInputBuffer;
    std::vector<float> convOutputBuffer;
    
    // Toggles
    bool useConvolution;
    bool useAlgorithmic;

    // Faust DSP object for the algorithmic reverb
    mydsp algoReverb;

    // We need a small scratch area for passing audio into/out of the Faust DSP
    // because it expects 2 inputs and 2 outputs (stereo).
    std::vector<float> dspInChannel0;
    std::vector<float> dspInChannel1;
    std::vector<float> dspOutChannel0;
    std::vector<float> dspOutChannel1;
};

///////////////////////////////////////////////////////////////////////////////
// PortAudio callback
///////////////////////////////////////////////////////////////////////////////
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData) 
{
    MyAudioData* data = static_cast<MyAudioData*>(userData);
    const float* in = static_cast<const float*>(inputBuffer);
    float* out = static_cast<float*>(outputBuffer);

    // If PortAudio gave us a null input or output, just clear the output and continue
    if (!in || !out) 
    {
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    // Verify the block size is what we expect
    if (framesPerBuffer != data->blockSize) 
    {
        std::cerr << "Block size mismatch! Check configuration.\n";
        std::memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    //-------------------------------------------------------------------------
    // 1) First stage: Convolution Reverb (if enabled)
    //-------------------------------------------------------------------------
    if (data->useConvolution) 
    {
        // Process block with the convolution
        // Input -> convolver -> convOutputBuffer
        data->convolver.process(in, data->convOutputBuffer.data(), framesPerBuffer);
    }
    else 
    {
        // Bypass convolution by copying input directly to convOutputBuffer
        std::memcpy(data->convOutputBuffer.data(), in, framesPerBuffer * sizeof(float));
    }

    //-------------------------------------------------------------------------
    // 2) Second stage: Algorithmic Reverb (if enabled)
    //    The Faust-generated code is stereo in/out. We'll feed the same mono 
    //    signal to the left and right inputs, then average the left/right outs.
    //-------------------------------------------------------------------------
    if (data->useAlgorithmic)
    {
        // Prepare the input for the Faust DSP: same signal on both channels
        for (unsigned long i = 0; i < framesPerBuffer; i++) 
        {
            data->dspInChannel0[i] = data->convOutputBuffer[i];
            data->dspInChannel1[i] = data->convOutputBuffer[i];
        }

        // Build arrays for Faust dsp->compute(...) call
        float* dspInputs[2]  = { data->dspInChannel0.data(),  data->dspInChannel1.data() };
        float* dspOutputs[2] = { data->dspOutChannel0.data(), data->dspOutChannel1.data() };

        // Run the Faust DSP processing
        data->algoReverb.compute(framesPerBuffer, dspInputs, dspOutputs);

        // Now mixdown the stereo out to mono
        for (unsigned long i = 0; i < framesPerBuffer; i++) 
        {
            // simple average of L and R
            out[i] = 0.5f * (data->dspOutChannel0[i] + data->dspOutChannel1[i]);
        }
    }
    else
    {
        // Bypass algorithmic reverb by copying the convOutputBuffer directly to out
        std::memcpy(out, data->convOutputBuffer.data(), framesPerBuffer * sizeof(float));
    }

    return paContinue;
}

///////////////////////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) 
{
    //--------------------------------------------------------------------------
    // 0) Usage / Command-Line Parsing
    //--------------------------------------------------------------------------
    if (argc < 4) {
        std::cerr << "Usage:\n  "
                  << argv[0] << " <ImpulseResponse.wav> <blockSize> <tailBlockSize> "
                  << "[useConv=1] [useAlgo=1] [dryWet=0.2] [damping=0.2] [roomSize=0.9] [preDelay=0.0] "
                  << "[lfo1Freq=0.0] [lfo1Depth=0.0] [lfo2Freq=0.0] [lfo2Depth=0.0]\n\n"
                  << "Example:\n  "
                  << argv[0] << " myImpulse.wav 1024 1024 1 1 0.5 0.2 0.9 0.03 1.0 50.0 0.5 20.0\n";
        return 1;
    }

    // Required arguments
    const std::string irPath = argv[1];
    const size_t blockSize   = fftconvolver::NextPowerOf2(std::stoul(argv[2]));
    const size_t tailBlockSize = fftconvolver::NextPowerOf2(std::stoul(argv[3]));

    // Optional toggles
    bool useConv = true;
    if (argc > 4) {
        useConv = (std::stoi(argv[4]) != 0);
    }
    bool useAlgo = true;
    if (argc > 5) {
        useAlgo = (std::stoi(argv[5]) != 0);
    }

    // Now parse the Faust parameters if given; otherwise use defaults from the dsp
    // We'll read up to 8 parameters (in the same order as the Faust dsp):
    //    fHslider0 = dryWet,
    //    fHslider1 = damping,
    //    fHslider2 = roomSize,
    //    fHslider3 = preDelay,
    //    fHslider6 = lfo1Freq,
    //    fHslider7 = lfo1Depth,
    //    fHslider4 = lfo2Freq,
    //    fHslider5 = lfo2Depth
    //
    // IMPORTANT: the order in the FAUST code is:
    //   0) Room Size  => fHslider2
    //   1) Damping    => fHslider1
    //   2) Pre Delay  => fHslider3
    //   3) LFO1 Freq  => fHslider6
    //   4) LFO1 Depth => fHslider7
    //   5) LFO2 Freq  => fHslider4
    //   6) LFO2 Depth => fHslider5
    //   7) Dry/Wet    => fHslider0
    //
    // but in the UI, "Dry/Wet" is last. So below we must set carefully.

    float dryWet   = 0.2f;   // fHslider0
    float damping  = 0.2f;   // fHslider1
    float roomSize = 0.9f;   // fHslider2
    float preDelay = 0.0f;   // fHslider3
    float lfo1Freq   = 0.0f; // fHslider6
    float lfo1Depth  = 0.0f; // fHslider7
    float lfo2Freq   = 0.0f; // fHslider4
    float lfo2Depth  = 0.0f; // fHslider5

    // If we have additional parameters on the command line:
    int index = 6;
    if (argc > index) { dryWet   = std::stof(argv[index++]); }
    if (argc > index) { damping  = std::stof(argv[index++]); }
    if (argc > index) { roomSize = std::stof(argv[index++]); }
    if (argc > index) { preDelay = std::stof(argv[index++]); }
    if (argc > index) { lfo1Freq   = std::stof(argv[index++]); }
    if (argc > index) { lfo1Depth  = std::stof(argv[index++]); }
    if (argc > index) { lfo2Freq   = std::stof(argv[index++]); }
    if (argc > index) { lfo2Depth  = std::stof(argv[index++]); }

    //--------------------------------------------------------------------------
    // 1) Load the impulse response file (must be 16-bit mono)
    //--------------------------------------------------------------------------
    WavData irWav;
    if (!LoadWavFile(irPath, irWav) || irWav.numChannels != 1 || irWav.bitsPerSample != 16) {
        std::cerr << "Invalid IR file. Must be 16-bit mono WAV.\n";
        return 1;
    }

    //--------------------------------------------------------------------------
    // 2) Prepare the convolution data
    //--------------------------------------------------------------------------
    MyAudioData audioData;
    audioData.blockSize = blockSize;
    audioData.useConvolution  = useConv;
    audioData.useAlgorithmic  = useAlgo;
    audioData.convInputBuffer.resize(blockSize);
    audioData.convOutputBuffer.resize(blockSize);

    // Initialize TwoStageFFTConvolver
    if (!audioData.convolver.init(blockSize, tailBlockSize,
                                  irWav.samples.data(), irWav.samples.size())) 
    {
        std::cerr << "Failed to initialize convolver.\n";
        return 1;
    }

    //--------------------------------------------------------------------------
    // 3) Initialize the Faust algorithmic reverb
    //--------------------------------------------------------------------------
    // We’ll open a PortAudio stream with a certain sample rate -> use that
    // below after we get it from the device. But we can at least create
    // the dsp object here.
    // The actual dsp->init(sampleRate) call will happen after we know sampleRate.
    // Meanwhile, set up the param memory or do it after dsp->init. 
    // We'll do it after sampleRate is known. For now, just store in struct:

    // We'll allocate memory for the two input channels and two output channels
    audioData.dspInChannel0.resize(blockSize);
    audioData.dspInChannel1.resize(blockSize);
    audioData.dspOutChannel0.resize(blockSize);
    audioData.dspOutChannel1.resize(blockSize);

    //--------------------------------------------------------------------------
    // 4) Initialize PortAudio
    //--------------------------------------------------------------------------
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // (a) Print available Host APIs
    int hostApiCount = Pa_GetHostApiCount();
    std::cout << "Available Host APIs:\n";
    for (int i = 0; i < hostApiCount; i++) {
        const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(i);
        if (apiInfo) {
            std::cout << "  [" << i << "] " << apiInfo->name 
                      << " (type=" << apiInfo->type << ")\n";
        }
    }

    // (b) Find the JACK host API
    PaHostApiIndex jackApiIndex = -1;
    for (int i = 0; i < hostApiCount; i++) {
        const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(i);
        if (apiInfo && apiInfo->type == paJACK) {
            jackApiIndex = i;
            break;
        }
    }
    if (jackApiIndex == -1) {
        std::cerr << "No JACK host found in PortAudio.\n"
                  << "Ensure PortAudio was built with JACK support.\n";
        Pa_Terminate();
        return 1;
    }

    // (c) Get the default input and output devices from the JACK host API
    const PaHostApiInfo* jackApiInfo = Pa_GetHostApiInfo(jackApiIndex);
    PaDeviceIndex inputDevice  = jackApiInfo->defaultInputDevice;
    PaDeviceIndex outputDevice = jackApiInfo->defaultOutputDevice;

    if (inputDevice == paNoDevice || outputDevice == paNoDevice) {
        std::cerr << "No default JACK input/output device found.\n";
        Pa_Terminate();
        return 1;
    }

    // (d) Set up PortAudio stream parameters (mono float32)
    PaStreamParameters inputParams;
    std::memset(&inputParams, 0, sizeof(inputParams));
    inputParams.device           = inputDevice;
    inputParams.channelCount     = 1;               // mono in
    inputParams.sampleFormat     = paFloat32;       // 32-bit float
    inputParams.suggestedLatency = 0.0;             // JACK manages latency

    PaStreamParameters outputParams;
    std::memset(&outputParams, 0, sizeof(outputParams));
    outputParams.device           = outputDevice;
    outputParams.channelCount     = 1;             // mono out
    outputParams.sampleFormat     = paFloat32;     // 32-bit float
    outputParams.suggestedLatency = 0.0;           // JACK manages latency

    // (e) Use JACK device's default sample rate
    double sampleRate = Pa_GetDeviceInfo(outputDevice)->defaultSampleRate;

    // Now we can properly init the Faust dsp with the known sampleRate
    audioData.algoReverb.init((int)sampleRate);

    // Set the Faust parameters
    audioData.algoReverb.fHslider0 = dryWet;    // "Dry/Wet"
    audioData.algoReverb.fHslider1 = damping;   // "Damping"
    audioData.algoReverb.fHslider2 = roomSize;  // "Room Size"
    audioData.algoReverb.fHslider3 = preDelay;  // "Pre Delay"
    audioData.algoReverb.fHslider4 = lfo2Freq;  // "LFO2 Freq"
    audioData.algoReverb.fHslider5 = lfo2Depth; // "LFO2 Depth"
    audioData.algoReverb.fHslider6 = lfo1Freq;  // "LFO1 Freq"
    audioData.algoReverb.fHslider7 = lfo1Depth; // "LFO1 Depth"

    // (f) Finally, open the PortAudio stream
    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParams,
        &outputParams,
        sampleRate,
        (unsigned long)blockSize,  // framesPerBuffer
        paNoFlag,
        audioCallback,
        &audioData
    );
    if (err != paNoError) {
        std::cerr << "Failed to open audio stream: " 
                  << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // (g) Start audio processing
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Failed to start stream: " 
                  << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Running real-time Reverb via JACK.\n"
              << "Sample Rate: "     << sampleRate << " Hz\n"
              << "Block Size: "      << blockSize << "\n"
              << "Tail Block Size: " << tailBlockSize << "\n"
              << "Convolution Reverb: " << (useConv ? "ON" : "OFF") << "\n"
              << "Algorithmic Reverb: " << (useAlgo ? "ON" : "OFF") << "\n"
              << "Press ENTER to quit...\n";
    std::cin.get();

    // (h) Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
