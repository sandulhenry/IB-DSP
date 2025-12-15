#include <IBDSP/waveforms/sine.hpp>

#include <cmath>

#define TWOPI 6.283185307

namespace IBDSP::waveforms
{

    vector<float> generateSineWave(
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift)
    {
        std::vector<float> buffer(numSamples);
        float phase = phase_shift; // start from the phase shift
        float phaseInc = TWOPI * frequency / sampleRate;

        for (int i = 0; i < numSamples; ++i)
        {
            buffer[i] = std::sin(phase);

            phase += phaseInc;
            if (phase >= TWOPI)
            {
                phase -= TWOPI; // wrap phase
            }
            else if (phase < 0.0f)
            {
                phase += TWOPI; // handle negative phase
            }
        }

        return buffer;
    }

}
