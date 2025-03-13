#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>

// Convolution reverb
#include "/home/Cullen/FYP/Effects/Effects/include/TwoStageFFTConvolver.h"
#include "/home/Cullen/FYP/Effects/Effects/include/Utilities.h"
#include "/home/Cullen/FYP/Effects/Effects/include/WavFile.h"

// Include the modified Faust algorithmic reverb code, which
// defines class "AlgoVerbDSP" and has public fHsliderN fields
// plus setter methods (setRoomSize, setDamping, etc.).
#include "/home/Cullen/FYP/Effects/Effects/faust_programs/algorithmicReverb.cpp"

//-----------------------------------------------------------
// Data structure to hold all processing data
//-----------------------------------------------------------
struct MyAudioData
{
    // Convolution
    fftconvolver::TwoStageFFTConvolver convolver;
    size_t blockSize;
    std::vector<float> convOutputBuffer;

    // Our Faust DSP class is "AlgoVerbDSP"
    AlgoVerbDSP algoReverb;

    // Toggles
    bool useConvolution;
    bool useAlgorithmic;

    // Temp buffers for the Faust DSP
    std::vector<float> dspIn0, dspIn1;   // 2 input channels
    std::vector<float> dspOut0, dspOut1; // 1 output channel in code, but let's handle as if 2 for future expansion
};

//-----------------------------------------------------------
// The audio callback
//-----------------------------------------------------------
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* /*timeInfo*/,
                         PaStreamCallbackFlags /*statusFlags*/,
                         void* userData) 
{
    MyAudioData* data = static_cast<MyAudioData*>(userData);
    const float* in = static_cast<const float*>(inputBuffer);
    float* out = static_cast<float*>(outputBuffer);

    if (!in || !out) {
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    if (framesPerBuffer != data->blockSize) {
        std::cerr << "Block size mismatch! Check configuration.\n";
        std::memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    //-------------------------------------------------------
    // 1) Convolution Reverb in MONO (if enabled)
    //-------------------------------------------------------
    if (data->useConvolution) {
        data->convolver.process(in, data->convOutputBuffer.data(), framesPerBuffer);
    } else {
        // Bypass
        std::memcpy(data->convOutputBuffer.data(), in, framesPerBuffer * sizeof(float));
    }

    //-------------------------------------------------------
    // 2) Algorithmic Reverb in series (if enabled)
    //    Faust DSP expects 2 input channels -> 1 output
    //-------------------------------------------------------
    if (data->useAlgorithmic) {
        // Duplicate mono -> dspIn0 and dspIn1
        for (unsigned long i = 0; i < framesPerBuffer; i++) {
            data->dspIn0[i] = data->convOutputBuffer[i];
            data->dspIn1[i] = data->convOutputBuffer[i];
        }

        // Our Faust DSP has 1 output
        float* dspInputs[2]  = { data->dspIn0.data(), data->dspIn1.data() };
        float* dspOutputs[1] = { data->dspOut0.data() };

        // Process
        data->algoReverb.compute(framesPerBuffer, dspInputs, dspOutputs);

        // Copy output
        std::memcpy(out, data->dspOut0.data(), framesPerBuffer * sizeof(float));
    }
    else {
        // Bypass algorithmic
        std::memcpy(out, data->convOutputBuffer.data(), framesPerBuffer * sizeof(float));
    }

    return paContinue;
}

//-----------------------------------------------------------
// Main
//-----------------------------------------------------------
int main(int argc, char* argv[])
{
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0]
                  << " <ImpulseResponse.wav> <blockSize> <tailBlockSize>"
                  << " <useConv=1> <useAlgo=1>"
                  << " [roomSize=0.9] [damping=0.2] [preDelay=0.02]"
                  << " [modFreq=0.2] [modDepth=2.0] [dryWet=0.4]\n";
        return 1;
    }

    // Required arguments
    const std::string irPath = argv[1];
    size_t blockSize   = fftconvolver::NextPowerOf2(std::stoul(argv[2]));
    size_t tailBlockSize = fftconvolver::NextPowerOf2(std::stoul(argv[3]));
    bool useConv = (std::stoi(argv[4]) != 0);
    bool useAlgo = (std::stoi(argv[5]) != 0);

    // Faust Reverb param defaults
    float roomSize = 0.9f;
    float damping  = 0.2f;
    float preDelay = 0.02f;
    float modFreq  = 0.2f;
    float modDepth = 2.0f;
    float dryWet   = 0.4f;

    // Optional parameters from the command line
    int index = 6;
    if (argc > index) { roomSize = std::stof(argv[index++]); }
    if (argc > index) { damping  = std::stof(argv[index++]); }
    if (argc > index) { preDelay = std::stof(argv[index++]); }
    if (argc > index) { modFreq  = std::stof(argv[index++]); }
    if (argc > index) { modDepth = std::stof(argv[index++]); }
    if (argc > index) { dryWet   = std::stof(argv[index++]); }

    // Load IR
    WavData irWav;
    if (!LoadWavFile(irPath, irWav) || irWav.numChannels != 1 || irWav.bitsPerSample != 16) {
        std::cerr << "Invalid IR file. Must be 16-bit mono WAV.\n";
        return 1;
    }

    // Prepare data
    MyAudioData audioData;
    audioData.blockSize      = blockSize;
    audioData.useConvolution = useConv;
    audioData.useAlgorithmic = useAlgo;
    audioData.convOutputBuffer.resize(blockSize);

    // Faust DSP buffers
    audioData.dspIn0.resize(blockSize);
    audioData.dspIn1.resize(blockSize);
    audioData.dspOut0.resize(blockSize);
    audioData.dspOut1.resize(blockSize);

    // Init convolution
    if (!audioData.convolver.init(blockSize, tailBlockSize,
                                  irWav.samples.data(), irWav.samples.size()))
    {
        std::cerr << "Failed to init convolution.\n";
        return 1;
    }

    // Init PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Pa_Initialize error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // Print Host APIs
    int hostApiCount = Pa_GetHostApiCount();
    std::cout << "Available Host APIs:\n";
    for (int i = 0; i < hostApiCount; i++) {
        const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(i);
        if (apiInfo) {
            std::cout << "  [" << i << "] " << apiInfo->name
                      << " (type=" << apiInfo->type << ")\n";
        }
    }

    // Find JACK
    PaHostApiIndex jackApiIndex = -1;
    for (int i = 0; i < hostApiCount; i++) {
        const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(i);
        if (apiInfo && apiInfo->type == paJACK) {
            jackApiIndex = i;
            break;
        }
    }
    if (jackApiIndex == -1) {
        std::cerr << "No JACK host found.\n";
        Pa_Terminate();
        return 1;
    }

    // Default JACK devices
    const PaHostApiInfo* jackApiInfo = Pa_GetHostApiInfo(jackApiIndex);
    PaDeviceIndex inputDevice  = jackApiInfo->defaultInputDevice;
    PaDeviceIndex outputDevice = jackApiInfo->defaultOutputDevice;
    if (inputDevice == paNoDevice || outputDevice == paNoDevice) {
        std::cerr << "No default JACK input/output device.\n";
        Pa_Terminate();
        return 1;
    }

    // Mono float32
    PaStreamParameters inputParams;
    std::memset(&inputParams, 0, sizeof(inputParams));
    inputParams.device           = inputDevice;
    inputParams.channelCount     = 1;
    inputParams.sampleFormat     = paFloat32;
    inputParams.suggestedLatency = 0.0;

    PaStreamParameters outputParams;
    std::memset(&outputParams, 0, sizeof(outputParams));
    outputParams.device           = outputDevice;
    outputParams.channelCount     = 1;
    outputParams.sampleFormat     = paFloat32;
    outputParams.suggestedLatency = 0.0;

    double sampleRate = Pa_GetDeviceInfo(outputDevice)->defaultSampleRate;

    // ----------------------------------------------------------
    // Init Faust reverb
    // ----------------------------------------------------------
    audioData.algoReverb.init((int)sampleRate);

    // Set Faust parameters from the command line
    audioData.algoReverb.setRoomSize(roomSize);
    audioData.algoReverb.setDamping(damping);
    audioData.algoReverb.setPreDelay(preDelay);
    audioData.algoReverb.setModFrequency(modFreq);
    audioData.algoReverb.setModDepth(modDepth);
    audioData.algoReverb.setDryWet(dryWet);

    // Open the stream
    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParams,
        &outputParams,
        sampleRate,
        (unsigned long)blockSize,
        paNoFlag,
        audioCallback,
        &audioData
    );
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // Start audio
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Running real-time convolution + algorithmic reverb in series.\n"
              << "Sample Rate = " << sampleRate << "\n"
              << "Block Size = " << blockSize << "\n"
              << "Tail Block Size = " << tailBlockSize << "\n"
              << "Convolution Reverb: " << (useConv ? "ON" : "OFF") << "\n"
              << "Algorithmic Reverb: " << (useAlgo ? "ON" : "OFF") << "\n"
              << "Press ENTER to quit...\n";

    std::cin.get();

    // Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
