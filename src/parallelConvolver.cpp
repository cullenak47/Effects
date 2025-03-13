#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>
#include "/home/Cullen/FYP/Effects/Effects/include/TwoStageConvolverParallel.h"
#include "/home/Cullen/FYP/Effects/Effects/include/Utilities.h"
#include "/home/Cullen/FYP/Effects/Effects/include/WavFile.h"

struct MyAudioData {
    fftconvolver::TwoStageFFTConvolverParallel convolver;
    size_t blockSize;
    std::vector<float> inputBuffer;
    std::vector<float> outputBuffer;
};

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

    if (!in || !out) {
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    // Verify block size matches expected configuration
    if (framesPerBuffer != data->blockSize) {
        std::cerr << "Block size mismatch! Check configuration.\n";
        std::memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    // Process the convolution using the parallel convolver
    data->convolver.process(in, data->outputBuffer.data(), data->blockSize);

    // Copy processed output to the stream's output buffer
    std::memcpy(out, data->outputBuffer.data(), framesPerBuffer * sizeof(float));

    return paContinue;
}

int main(int argc, char* argv[]) 
{
    // Check command-line args
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] 
                  << " <ImpulseResponse.wav> <blockSize> <tailBlockSize>\n";
        return 1;
    }

    // Parse command-line parameters
    const std::string irPath = argv[1];
    const size_t blockSize = fftconvolver::NextPowerOf2(std::stoul(argv[2]));
    const size_t tailBlockSize = fftconvolver::NextPowerOf2(std::stoul(argv[3]));
    const unsigned long framesPerBuffer = blockSize;  // Force alignment

    // Load impulse response (must be 16-bit mono)
    WavData irWav;
    if (!LoadWavFile(irPath, irWav) || irWav.numChannels != 1 || irWav.bitsPerSample != 16) {
        std::cerr << "Invalid IR file. Must be 16-bit mono WAV.\n";
        return 1;
    }

    // Prepare the convolution data
    MyAudioData audioData;
    audioData.blockSize = blockSize;
    audioData.inputBuffer.resize(blockSize);
    audioData.outputBuffer.resize(blockSize);

    // Initialize the TwoStageFFTConvolverParallel
    if (!audioData.convolver.init(blockSize, tailBlockSize,
                                  irWav.samples.data(), irWav.samples.size())) 
    {
        std::cerr << "Failed to initialize convolver.\n";
        return 1;
    }

    // Initialize PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // -------------------------------------------------------------------------
    // (1) Print available Host APIs (for debugging)
    int hostApiCount = Pa_GetHostApiCount();
    std::cout << "Available Host APIs:\n";
    for (int i = 0; i < hostApiCount; i++) {
        const PaHostApiInfo* apiInfo = Pa_GetHostApiInfo(i);
        if (apiInfo) {
            std::cout << "  [" << i << "] " << apiInfo->name 
                      << " (type=" << apiInfo->type << ")\n";
        }
    }

    // -------------------------------------------------------------------------
    // (2) Find the JACK host API
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

    // -------------------------------------------------------------------------
    // (3) Get the default input and output devices from the JACK host API
    const PaHostApiInfo* jackApiInfo = Pa_GetHostApiInfo(jackApiIndex);
    PaDeviceIndex inputDevice = jackApiInfo->defaultInputDevice;
    PaDeviceIndex outputDevice = jackApiInfo->defaultOutputDevice;

    if (inputDevice == paNoDevice || outputDevice == paNoDevice) {
        std::cerr << "No default JACK input/output device found.\n";
        Pa_Terminate();
        return 1;
    }

    // -------------------------------------------------------------------------
    // (4) Set up the PortAudio stream parameters for JACK (mono float32)
    PaStreamParameters inputParams;
    std::memset(&inputParams, 0, sizeof(inputParams));
    inputParams.device = inputDevice;
    inputParams.channelCount = 1;               // mono
    inputParams.sampleFormat = paFloat32;       // 32-bit float
    inputParams.suggestedLatency = 0.0;           // JACK manages latency
    inputParams.hostApiSpecificStreamInfo = nullptr;

    PaStreamParameters outputParams;
    std::memset(&outputParams, 0, sizeof(outputParams));
    outputParams.device = outputDevice;
    outputParams.channelCount = 1;              // mono
    outputParams.sampleFormat = paFloat32;      // 32-bit float
    outputParams.suggestedLatency = 0.0;          // JACK manages latency
    outputParams.hostApiSpecificStreamInfo = nullptr;

    // (5) Use JACK device's default sample rate
    double sampleRate = Pa_GetDeviceInfo(outputDevice)->defaultSampleRate;

    // -------------------------------------------------------------------------
    // (6) Open the PortAudio stream using the JACK host API
    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParams,
        &outputParams,
        sampleRate,
        framesPerBuffer,
        paNoFlag,
        audioCallback,
        &audioData
    );
    if (err != paNoError) {
        std::cerr << "Failed to open audio stream: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // (7) Start audio processing
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Failed to start stream: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Running real-time convolution via JACK.\n"
              << "Sample Rate: " << sampleRate << " Hz, "
              << "Block Size: " << blockSize << ", "
              << "Tail Block Size: " << tailBlockSize << "\n"
              << "Press ENTER to quit...\n";
    std::cin.get();

    // (8) Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
