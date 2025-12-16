#include <IBDSP/waveforms/sine.hpp>
#include <IBDSP/waveforms/common.hpp>

#include <cmath>

namespace IBDSP::waveforms
{
    std::vector<float> generateSineWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase
    )
    {
        std::vector<float> buffer(numSamples);

        const float phaseInc = TWO_PI * frequency / sampleRate;

        // Normalize phase
        phase = std::fmod(phase, TWO_PI);
        if (phase < 0.0f) phase += TWO_PI;

        for (int i = 0; i < numSamples; ++i)
        {
            buffer[i] = amplitude * std::sin(phase);

            phase += phaseInc;
            if (phase >= TWO_PI)
                phase -= TWO_PI;
        }

        return buffer;
    }
}
