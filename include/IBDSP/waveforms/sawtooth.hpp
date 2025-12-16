#pragma once

#include <vector>

namespace IBDSP::waveforms
{
    /**
     * Generate a naive sawtooth wave buffer.
     *
     * NOTE: This implementation is not band-limited and will alias.
     *
     * @param descending  true for descending slope, false for ascending
     */
    std::vector<float> generateSawtoothWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase = 0.0f,
        bool  descending = false
    );
}
