#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>
#include "/home/Cullen/FYP/convReverb/Convolutional-Reverberator/include/TwoStageFFTConvolver.h"
#include "/home/Cullen/FYP/convReverb/Convolutional-Reverberator/include/Utilities.h"
#include "/home/Cullen/FYP/convReverb/Convolutional-Reverberator/include/WavFile.h"

struct MyAudioData {
    fftconvolver::TwoStageFFTConvolver convolver;
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
        if (out) memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    // Verify block size matches expected configuration
    if (framesPerBuffer != data->blockSize) {
        std::cerr << "Block size mismatch! Check configuration.\n";
        memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    // Direct processing without accumulation
    data->convolver.process(in, data->outputBuffer.data(), data->blockSize);
    
    // Copy processed output
    memcpy(out, data->outputBuffer.data(), framesPerBuffer * sizeof(float));

    return paContinue;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] 
                  << " <ImpulseResponse.wav> <blockSize> <tailBlockSize>\n";
        return 1;
    }

    // Configuration parameters
    const std::string irPath = argv[1];
    const size_t blockSize = fftconvolver::NextPowerOf2(std::stoul(argv[2]));
    const size_t tailBlockSize = fftconvolver::NextPowerOf2(std::stoul(argv[3]));
    const unsigned long framesPerBuffer = blockSize;  // Force alignment

    // Load impulse response
    WavData irWav;
    if (!LoadWavFile(irPath, irWav) || irWav.numChannels != 1 || irWav.bitsPerSample != 16) {
        std::cerr << "Invalid IR file. Must be 16-bit mono WAV.\n";
        return 1;
    }

    // Initialize audio data
    MyAudioData audioData;
    audioData.blockSize = blockSize;
    audioData.inputBuffer.resize(blockSize);
    audioData.outputBuffer.resize(blockSize);
    
    if (!audioData.convolver.init(blockSize, tailBlockSize, 
                                 irWav.samples.data(), irWav.samples.size())) {
        std::cerr << "Failed to initialize convolver.\n";
        return 1;
    }

    // PortAudio initialization
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // Configure low-latency device parameters
    PaStreamParameters inputParams, outputParams;
    const PaDeviceIndex inputDevice = Pa_GetDefaultInputDevice();
    const PaDeviceIndex outputDevice = Pa_GetDefaultOutputDevice();

    if (inputDevice == paNoDevice || outputDevice == paNoDevice) {
        std::cerr << "No default audio devices found.\n";
        Pa_Terminate();
        return 1;
    }

    // Set up input parameters with minimum latency
    inputParams.device = inputDevice;
    inputParams.channelCount = 1;
    inputParams.sampleFormat = paFloat32;
    inputParams.suggestedLatency = Pa_GetDeviceInfo(inputDevice)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    // Set up output parameters with minimum latency
    outputParams.device = outputDevice;
    outputParams.channelCount = 1;
    outputParams.sampleFormat = paFloat32;
    outputParams.suggestedLatency = Pa_GetDeviceInfo(outputDevice)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = nullptr;

    // Open stream with optimized settings
    PaStream* stream;
    const double sampleRate = Pa_GetDeviceInfo(outputDevice)->defaultSampleRate;
    
    err = Pa_OpenStream(&stream,
                        &inputParams,
                        &outputParams,
                        sampleRate,
                        framesPerBuffer,
                        paNoFlag,
                        audioCallback,
                        &audioData);

    if (err != paNoError) {
        std::cerr << "Failed to open audio stream: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // Start audio processing
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Failed to start stream: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Running real-time convolution (Latency: " 
              << (blockSize / sampleRate * 1000) << "ms)\n"
              << "Press ENTER to quit...\n";
    std::cin.get();

    // Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}