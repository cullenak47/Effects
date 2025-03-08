#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>

// Include your FFTConvolver library headers
#include "FFTConvolver.h"
#include "Utilities.h"
#include "WavFile.h"

// A struct for our audio callback's user data
struct MyAudioData
{
    fftconvolver::FFTConvolver convolver;  // Convolver is stored directly here
    size_t blockSize;

    // Overlap buffer for collecting input samples up to blockSize
    std::vector<float> inputOverlap;
    size_t inputOverlapFill;

    // Temporary buffer to hold convolver output for each block
    std::vector<float> convolverOutput;
};

// PortAudio callback function
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData)
{
    MyAudioData* audioData = reinterpret_cast<MyAudioData*>(userData);

    const float* in = static_cast<const float*>(inputBuffer);
    float*       out = static_cast<float*>(outputBuffer);

    if (!in || !out)
    {
        // If either buffer is null, fill output with silence (or do nothing).
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    size_t processed  = 0;
    size_t remaining  = framesPerBuffer;
    const size_t blk  = audioData->blockSize;

    // Clear the output buffer so we can add convolver output to it
    std::memset(out, 0, framesPerBuffer * sizeof(float));

    // Accumulate incoming samples into our overlap buffer.
    while (remaining > 0)
    {
        size_t freeSpace = blk - audioData->inputOverlapFill; 
        size_t todo = (remaining < freeSpace) ? remaining : freeSpace;

        // Copy from 'in' to the overlap buffer
        std::memcpy(audioData->inputOverlap.data() + audioData->inputOverlapFill,
                    in + processed,
                    todo * sizeof(float));

        audioData->inputOverlapFill += todo;
        processed += todo;
        remaining -= todo;

        // If we've filled a full block, run the convolver
        if (audioData->inputOverlapFill == blk)
        {
            // Zero out the convolverOutput buffer
            std::fill(audioData->convolverOutput.begin(),
                      audioData->convolverOutput.end(),
                      0.0f);

            // Convolve the block
            audioData->convolver.process(
                audioData->inputOverlap.data(),
                audioData->convolverOutput.data(),
                blk
            );

            // Mix convolver output into the PortAudio output buffer
            // The start offset in 'out' is (processed - blk)
            size_t offset = processed - blk;
            // Make sure we don't write beyond framesPerBuffer
            size_t toWrite = std::min<size_t>(blk, framesPerBuffer - offset);

            for (size_t i = 0; i < toWrite; i++)
            {
                out[offset + i] += audioData->convolverOutput[i];
            }

            // Reset overlap fill for next block
            audioData->inputOverlapFill = 0;
        }
    }

    return paContinue;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <ImpulseResponse.wav> <blockSize>\n";
        return 1;
    }

    const std::string irFilePath = argv[1];
    size_t blockSize = static_cast<size_t>(std::stoi(argv[2]));

    // --- 1) Load IR from a mono, 16-bit WAV ---
    WavData irWav;
    if (!LoadWavFile(irFilePath, irWav))
    {
        std::cerr << "Error: Could not load IR file: " << irFilePath << "\n";
        return 1;
    }
    if (irWav.numChannels != 1 || irWav.bitsPerSample != 16)
    {
        std::cerr << "Error: IR must be mono, 16-bit.\n";
        return 1;
    }

    // Ensure blockSize is a power of 2
    blockSize = fftconvolver::NextPowerOf2(blockSize);

    // --- 2) Prepare the user data with FFTConvolver inside ---
    MyAudioData audioData;
    audioData.blockSize = blockSize;
    audioData.inputOverlap.resize(blockSize, 0.0f);
    audioData.inputOverlapFill = 0;
    audioData.convolverOutput.resize(blockSize, 0.0f);

    // Initialize the convolver
    if (!audioData.convolver.init(blockSize, 
                                  irWav.samples.data(),
                                  irWav.samples.size()))
    {
        std::cerr << "Convolver init failed.\n";
        return 1;
    }

    // --- 3) Initialize PortAudio ---
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Pa_Initialize() error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // Prepare input and output stream parameters
    PaStreamParameters inputParams;
    inputParams.device                    = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        std::cerr << "Error: No default input device.\n";
        Pa_Terminate();
        return 1;
    }
    inputParams.channelCount              = 1;        // mono
    inputParams.sampleFormat              = paFloat32;
    inputParams.suggestedLatency          = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    PaStreamParameters outputParams;
    outputParams.device                   = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cerr << "Error: No default output device.\n";
        Pa_Terminate();
        return 1;
    }
    outputParams.channelCount             = 1;       // mono
    outputParams.sampleFormat             = paFloat32;
    outputParams.suggestedLatency         = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo= nullptr;

    double sampleRate = Pa_GetDeviceInfo(outputParams.device)->defaultSampleRate;
    // framesPerBuffer is how many frames (samples for mono) per audio callback.
    // For guitar or real-time effects, 256 is often a decent compromise.
    unsigned long framesPerBuffer = 256; 

    // --- 4) Open the stream ---
    PaStream* stream;
    err = Pa_OpenStream(&stream,
                        &inputParams,
                        &outputParams,
                        sampleRate,
                        framesPerBuffer,
                        paNoFlag,
                        audioCallback,
                        &audioData);
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream() error: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // --- 5) Start the stream ---
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream() error: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    std::cout << "Real-time convolution running.\n";
    std::cout << "Press ENTER to stop.\n";
    std::cin.get(); // Wait for user input

    // --- 6) Stop and close the stream ---
    Pa_StopStream(stream);
    Pa_CloseStream(stream);

    // --- 7) Clean up PortAudio ---
    Pa_Terminate();

    std::cout << "Done.\n";
    return 0;
}
