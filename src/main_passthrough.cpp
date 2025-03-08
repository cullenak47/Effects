#include <iostream>
#include <cstring>
#include <portaudio.h>

/**
 * @brief Simple pass-through callback: copies audio from input to output, unaltered.
 */
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData)
{
    // Cast to float pointers for simplicity (mono float32)
    const float* in = static_cast<const float*>(inputBuffer);
    float* out      = static_cast<float*>(outputBuffer);

    // If input or output is null, fill with silence to avoid noise
    if (!in || !out) {
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    // Pass-through: copy input directly to output
    std::memcpy(out, in, framesPerBuffer * sizeof(float));

    return paContinue;
}


int main(int argc, char* argv[])
{
    // Optionally allow framesPerBuffer as an argument
    unsigned long framesPerBuffer = 256; 
    if (argc >= 2) {
        framesPerBuffer = static_cast<unsigned long>(std::stoi(argv[1]));
    }

    // Initialize PortAudio
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "Pa_Initialize error: " << Pa_GetErrorText(err) << "\n";
        return 1;
    }

    // Prepare input and output parameters for mono float32
    PaStreamParameters inputParams, outputParams;

    // Default input
    inputParams.device = Pa_GetDefaultInputDevice();
    if (inputParams.device == paNoDevice) {
        std::cerr << "Error: No default input device.\n";
        Pa_Terminate();
        return 1;
    }
    inputParams.channelCount              = 1;           // mono
    inputParams.sampleFormat              = paFloat32;   // 32-bit float
    inputParams.suggestedLatency          = Pa_GetDeviceInfo(inputParams.device)->defaultLowInputLatency;
    inputParams.hostApiSpecificStreamInfo = nullptr;

    // Default output
    outputParams.device = Pa_GetDefaultOutputDevice();
    if (outputParams.device == paNoDevice) {
        std::cerr << "Error: No default output device.\n";
        Pa_Terminate();
        return 1;
    }
    outputParams.channelCount             = 1;           // mono
    outputParams.sampleFormat             = paFloat32;   // 32-bit float
    outputParams.suggestedLatency         = Pa_GetDeviceInfo(outputParams.device)->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = nullptr;

    // Use the device's default sample rate
    double sampleRate = Pa_GetDeviceInfo(outputParams.device)->defaultSampleRate;

    // Open stream
    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParams,
        &outputParams,
        sampleRate,
        framesPerBuffer,
        paNoFlag,
        audioCallback,
        nullptr // no special userData needed
    );
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // Start stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    // Wait for user to press ENTER
    std::cout << "Pass-through running (mono). Press ENTER to stop.\n";
    std::cin.get();

    // Stop and close
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    std::cout << "Done.\n";
    return 0;
}
