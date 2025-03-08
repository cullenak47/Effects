#ifndef WAVFILE_H
#define WAVFILE_H

#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Simple container for WAV file data (mono only for this example)
 */
struct WavData
{
    uint32_t sampleRate = 0;
    uint16_t numChannels = 0;
    uint16_t bitsPerSample = 0;
    // Samples stored as float in range [-1.0, +1.0]
    std::vector<float> samples;
};

/**
 * @brief Loads a 16-bit mono WAV file into WavData (floating-point samples)
 * @return true on success, false on failure
 */
bool LoadWavFile(const std::string& filename, WavData& outWav);

/**
 * @brief Saves WavData (floating-point samples) to a 16-bit mono WAV file
 * @return true on success, false on failure
 */
bool SaveWavFile(const std::string& filename, const WavData& wav);

#endif // WAVFILE_H
