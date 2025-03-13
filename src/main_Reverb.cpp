#include <iostream>
#include <vector>
#include <cstring>
#include <portaudio.h>
#include "/home/Cullen/FYP/Effects/Effects/include/TwoStageFFTConvolver.h"
#include "/home/Cullen/FYP/Effects/Effects/include/Utilities.h"
#include "/home/Cullen/FYP/Effects/Effects/include/WavFile.h"
#include "/home/Cullen/FYP/Effects/Effects/faust_programs/algorithmicRev.h"  // Faust-generated header

struct MyAudioData {
    // Convolution Reverb
    fftconvolver::TwoStageFFTConvolver convolver;
    bool useConv = false;
    
    // Algorithmic Reverb
    AlgorithmicReverb algoReverb;
    bool useAlgo = false;
    
    // Buffers
    size_t blockSize;
    std::vector<float> inputBuffer;
    std::vector<float> outputBuffer;
    std::vector<float> tempBuffer;  // For chaining reverbs
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
        if (out) std::memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    // Validate block size
    if (framesPerBuffer != data->blockSize) {
        std::cerr << "Block size mismatch!\n";
        std::memset(out, 0, framesPerBuffer * sizeof(float));
        return paContinue;
    }

    // Process input through convolutional reverb
    if (data->useConv) {
        data->convolver.process(in, data->outputBuffer.data(), framesPerBuffer);
    } else {
        std::memcpy(data->outputBuffer.data(), in, framesPerBuffer * sizeof(float));
    }

    // Process through algorithmic reverb
    if (data->useAlgo) {
        data->algoReverb.process(
            data->outputBuffer.data(), 
            data->tempBuffer.data(), 
            framesPerBuffer
        );
        std::memcpy(data->outputBuffer.data(), 
                   data->tempBuffer.data(), 
                   framesPerBuffer * sizeof(float));
    }

    // Copy final output to stream
    std::memcpy(out, data->outputBuffer.data(), framesPerBuffer * sizeof(float));
    return paContinue;
}

void parseArgs(int argc, char* argv[], MyAudioData& data) {
    for (int i = 4; i < argc; i++) {
        if (strcmp(argv[i], "-conv") == 0) {
            data.useConv = true;
        } else if (strcmp(argv[i], "-algo") == 0) {
            data.useAlgo = true;
            // Parse algorithmic reverb parameters
            while (++i < argc) {
                if (strcmp(argv[i], "-room") == 0 && i+1 < argc) {
                    data.algoReverb.control("[0]Room Size [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-damp") == 0 && i+1 < argc) {
                    data.algoReverb.control("[1]Damping [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-predelay") == 0 && i+1 < argc) {
                    data.algoReverb.control("[3]Pre Delay [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-lfo1freq") == 0 && i+1 < argc) {
                    data.algoReverb.control("[4]LFO1 Freq [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-lfo1depth") == 0 && i+1 < argc) {
                    data.algoReverb.control("[5]LFO1 Depth [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-lfo2freq") == 0 && i+1 < argc) {
                    data.algoReverb.control("[6]LFO2 Freq [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-lfo2depth") == 0 && i+1 < argc) {
                    data.algoReverb.control("[7]LFO2 Depth [style:knob]", atof(argv[++i]));
                } else if (strcmp(argv[i], "-drywet") == 0 && i+1 < argc) {
                    data.algoReverb.control("[8]Dry/Wet", atof(argv[++i]));
                } else {
                    i--; // Backtrack for unknown params
                    break;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] 
                  << " <ImpulseResponse.wav> <blockSize> <tailBlockSize> "
                  << "[-conv] [-algo [params]]\n";
        return 1;
    }

    // Parse required arguments
    const std::string irPath = argv[1];
    const size_t blockSize = fftconvolver::NextPowerOf2(std::stoul(argv[2]));
    const size_t tailBlockSize = fftconvolver::NextPowerOf2(std::stoul(argv[3]));

    // Initialize audio data
    MyAudioData audioData;
    audioData.blockSize = blockSize;
    audioData.inputBuffer.resize(blockSize);
    audioData.outputBuffer.resize(blockSize);
    audioData.tempBuffer.resize(blockSize);

    // Parse optional flags
    parseArgs(argc, argv, audioData);

    // Load IR and initialize convolver if enabled
    if (audioData.useConv) {
        WavData irWav;
        if (!LoadWavFile(irPath, irWav) || irWav.numChannels != 1 || irWav.bitsPerSample != 16) {
            std::cerr << "Invalid IR file.\n";
            return 1;
        }
        if (!audioData.convolver.init(blockSize, tailBlockSize, 
                                    irWav.samples.data(), irWav.samples.size())) {
            std::cerr << "Failed to initialize convolver.\n";
            return 1;
        }
    }

    // PortAudio setup
    Pa_Initialize();
    PaStream* stream;
    PaHostApiIndex jackApiIndex = -1;
    // ... [Keep existing JACK setup code unchanged] ...

    // Get sample rate after opening stream
    double sampleRate = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->defaultSampleRate;

    // Initialize algorithmic reverb if enabled
    if (audioData.useAlgo) {
        audioData.algoReverb.init(sampleRate);
    }

    Pa_StartStream(stream);
    std::cout << "Running... Press Enter to quit.\n";
    std::cin.get();

    // Cleanup
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    return 0;
}
