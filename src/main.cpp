#include <iostream>
#include <cstring>
#include <portaudio.h>
#include <cstdlib>
#include "reverb.cpp"  // Generated Faust DSP

ReverbDSP reverb;

// PortAudio callback (same as before)
static int audioCallback(const void* inputBuffer,
                         void* outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData)
{
    ReverbDSP* dsp = static_cast<ReverbDSP*>(userData);

    const float* in = static_cast<const float*>(inputBuffer);
    float* out = static_cast<float*>(outputBuffer);

    if (!in || !out) {
        if (out) {
            std::memset(out, 0, framesPerBuffer * sizeof(float));
        }
        return paContinue;
    }

    float* inputs[1] = { const_cast<float*>(in) };
    float* outputs[1] = { out };

    dsp->compute(framesPerBuffer, inputs, outputs);

    return paContinue;
}

int main(int argc, char* argv[])
{
    double sampleRate = 44100;
    unsigned long framesPerBuffer = 256;

    if (argc > 1) framesPerBuffer = static_cast<unsigned long>(std::stoi(argv[1]));
    if (argc > 2) sampleRate = std::stod(argv[2]);

    reverb.init(static_cast<int>(sampleRate));

    // Optional: Set parameters via command-line arguments
    if (argc > 3) reverb.setParamValue("/Reverb/Room Size", std::stof(argv[3]));
    if (argc > 4) reverb.setParamValue("/Reverb/Damping", std::stof(argv[4]));
    if (argc > 5) reverb.setParamValue("/Reverb/Pre Delay", std::stof(argv[5]) * sampleRate);
    if (argc > 6) reverb.setParamValue("/Reverb/Mod Frequency", std::stof(argv[6]));
    if (argc > 7) reverb.setParamValue("/Reverb/Mod Depth", std::stof(argv[7]));
    if (argc > 8) reverb.setParamValue("/Reverb/Dry/Wet", std::stof(argv[8]));

    // PortAudio setup (same as before)...
    // (Omitted here for brevity; reuse from your working version.)

    return 0;
}
