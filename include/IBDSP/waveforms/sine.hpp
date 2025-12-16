#pragma once

#include <vector>

namespace IBDSP::waveforms
{
    /**
     * Generate a sine wave buffer.
     *
     * @param amplitude   Peak amplitude
     * @param frequency   Frequency in Hz
     * @param sampleRate  Sample rate in Hz
     * @param numSamples  Number of samples to generate
     * @param phase       Initial phase in radians
     */
    std::vector<float> generateSineWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase = 0.0f
    );
}
