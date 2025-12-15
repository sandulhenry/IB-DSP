#include <IBDSP/waveforms/square.hpp>

#include <cmath>

#define TWOPI 6.283185307

namespace IBDSP::waveforms{

    vector<float> generateSquareWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift ,
        float duty
    ){
        std::vector<float> buffer(numSamples);
        float phase = phase_shift; // initial
        
        float phaseInc = (float) TWOPI * frequency / sampleRate;

        for (int i = 0; i < numSamples; ++i) {
            // Square wave: +1 if sine >= 0, -1 if sine < 0
            float value = (phase / TWOPI < duty) ? 1.0f : -1.0f;
            value *= amplitude;
            buffer[i] = value;

            phase += phaseInc;
            if (phase >= TWOPI) phase -= (float) TWOPI; // wrap phase
        }

        return buffer;
    }
}