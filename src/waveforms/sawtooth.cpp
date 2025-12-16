#include <IBDSP/waveforms/sawtooth.hpp>

#include <cmath>
#include <vector>

#define TWOPI 6.283185307

namespace IBDSP::waveforms
{

    vector<float> generateSawtoothWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift,
        bool desc = false
        )
    {
        vector<float> buffer(numSamples);

        float phase = phase_shift;
        float phaseInc = TWOPI * frequency / sampleRate;

        for (int i = 0; i < numSamples; ++i)
        {
            // Normalize phase to [0, 1)
            float normPhase = phase / TWOPI;

            // Sawtooth in range [-1, 1)
            float value = desc 
            ? (1.0f - 2.0f * normPhase)   // descending
            : (2.0f * normPhase - 1.0f);  // ascending

            buffer[i] = amplitude * value;

            phase += phaseInc;
            if (phase >= TWOPI)
                phase -= TWOPI;
        }

        return buffer;
    }

}