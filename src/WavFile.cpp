#include "/home/Cullen/FYP/convReverb/Convolutional-Reverberator/include/WavFile.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <cstring>

#pragma pack(push, 1)
struct WAVHeader
{
    // RIFF chunk descriptor
    char     chunkID[4];    // "RIFF"
    uint32_t chunkSize;     // 36 + subChunk2Size
    char     format[4];     // "WAVE"

    // "fmt " sub-chunk
    char     subchunk1ID[4];    // "fmt "
    uint32_t subchunk1Size;     // 16 for PCM
    uint16_t audioFormat;       // 1 for PCM
    uint16_t numChannels;       // 1 for mono, 2 for stereo, etc.
    uint32_t sampleRate;        
    uint32_t byteRate;          // == SampleRate * NumChannels * BitsPerSample/8
    uint16_t blockAlign;        // == NumChannels * BitsPerSample/8
    uint16_t bitsPerSample;     // 8, 16, 24, or 32 bits

    // "data" sub-chunk
    char     subchunk2ID[4];    // "data"
    uint32_t subchunk2Size;     // == NumSamples * NumChannels * BitsPerSample/8
};
#pragma pack(pop)


bool LoadWavFile(const std::string& filename, WavData& outWav)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.good()) {
        std::cerr << "Error: Cannot open WAV file: " << filename << std::endl;
        return false;
    }

    WAVHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    if (file.gcount() < static_cast<std::streamsize>(sizeof(WAVHeader))) {
        std::cerr << "Error: Invalid WAV header (too small)\n";
        return false;
    }

    // Basic validation
    if (std::memcmp(header.chunkID, "RIFF", 4) != 0 ||
        std::memcmp(header.format,  "WAVE", 4) != 0 ||
        std::memcmp(header.subchunk1ID, "fmt ", 4) != 0 ||
        std::memcmp(header.subchunk2ID, "data", 4) != 0 ||
        header.audioFormat != 1 ||  // PCM?
        header.numChannels != 1 ||  // only mono in this example
        header.bitsPerSample != 16) // only 16-bit in this example
    {
        std::cerr << "Error: WAV file is not a 16-bit mono PCM file, or has broken header.\n";
        return false;
    }

    outWav.sampleRate = header.sampleRate;
    outWav.numChannels = header.numChannels;
    outWav.bitsPerSample = header.bitsPerSample;

    // Number of samples:
    const size_t numSamples = header.subchunk2Size / (header.numChannels * (header.bitsPerSample/8));
    outWav.samples.resize(numSamples);

    // Read sample data in 16-bit
    for (size_t i = 0; i < numSamples; i++) {
        int16_t sampleValue;
        file.read(reinterpret_cast<char*>(&sampleValue), sizeof(int16_t));
        // Convert to float [-1, +1]
        outWav.samples[i] = static_cast<float>(sampleValue) / 32768.0f;
    }

    return true;
}


bool SaveWavFile(const std::string& filename, const WavData& wav)
{
    if (wav.numChannels != 1 || wav.bitsPerSample != 16) {
        std::cerr << "Error: Only 16-bit mono supported in this example.\n";
        return false;
    }

    const size_t numSamples = wav.samples.size();
    WAVHeader header;

    // Fill RIFF/WAVE header
    std::memcpy(header.chunkID, "RIFF", 4);
    std::memcpy(header.format,  "WAVE", 4);
    std::memcpy(header.subchunk1ID, "fmt ", 4);
    std::memcpy(header.subchunk2ID, "data", 4);

    header.subchunk1Size = 16;
    header.audioFormat = 1;  // PCM
    header.numChannels = wav.numChannels;
    header.sampleRate  = wav.sampleRate;
    header.bitsPerSample = wav.bitsPerSample;
    header.byteRate = header.sampleRate * header.numChannels * (header.bitsPerSample/8);
    header.blockAlign = header.numChannels * (header.bitsPerSample/8);

    const uint32_t dataSize = static_cast<uint32_t>(numSamples * header.numChannels * (header.bitsPerSample/8));
    header.subchunk2Size = dataSize;
    header.chunkSize = 36 + dataSize;

    // Write file
    std::ofstream file(filename, std::ios::binary);
    if (!file.good()) {
        std::cerr << "Error: Cannot open output WAV file: " << filename << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));

    // Convert floats back to int16 and clamp
    for (size_t i = 0; i < numSamples; i++) {
        float fval = wav.samples[i];
        // clamp to [-1, +1]
        fval = std::max(-1.0f, std::min(1.0f, fval));
        int16_t ival = static_cast<int16_t>(fval * 32767.0f);
        file.write(reinterpret_cast<const char*>(&ival), sizeof(int16_t));
    }

    return true;
}
