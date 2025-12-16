#pragma once

#include <vector>

namespace IBDSP::waveforms
{
    /**
     * Generate a naive square wave buffer.
     *
     * NOTE: This implementation is not band-limited and will alias.
     *
     * @param duty Duty cycle in range (0, 1)
     */
    std::vector<float> generateSquareWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase = 0.0f,
        float duty  = 0.5f
    );
}
