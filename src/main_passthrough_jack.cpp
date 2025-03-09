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
    // (4) Prepare input and output parameters for mono float32 via JACK
    PaStreamParameters inputParams;
    std::memset(&inputParams, 0, sizeof(inputParams));
    inputParams.device = inputDevice;
    inputParams.channelCount = 1;           // mono
    inputParams.sampleFormat = paFloat32;   // 32-bit float
    inputParams.suggestedLatency = 0.0;     // JACK manages latency
    inputParams.hostApiSpecificStreamInfo = nullptr;

    PaStreamParameters outputParams;
    std::memset(&outputParams, 0, sizeof(outputParams));
    outputParams.device = outputDevice;
    outputParams.channelCount = 1;          // mono
    outputParams.sampleFormat = paFloat32;  // 32-bit float
    outputParams.suggestedLatency = 0.0;    // JACK manages latency
    outputParams.hostApiSpecificStreamInfo = nullptr;

    // -------------------------------------------------------------------------
    // (5) Use the device's default sample rate (as reported by the JACK device)
    double sampleRate = Pa_GetDeviceInfo(outputDevice)->defaultSampleRate;

    // (6) Open the stream using JACK
    PaStream* stream;
    err = Pa_OpenStream(
        &stream,
        &inputParams,
        &outputParams,
        sampleRate,
        framesPerBuffer,
        paNoFlag,           // or paClipOff, etc.
        audioCallback,
        nullptr
    );
    if (err != paNoError) {
        std::cerr << "Pa_OpenStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_Terminate();
        return 1;
    }

    // (7) Start the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "Pa_StartStream error: " << Pa_GetErrorText(err) << "\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }

    // -------------------------------------------------------------------------
    std::cout << "JACK pass-through (mono) running at " << sampleRate 
              << " Hz. Press ENTER to stop.\n";
    std::cin.get();

    // (8) Stop and close the stream
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    std::cout << "Done.\n";
    return 0;
}
