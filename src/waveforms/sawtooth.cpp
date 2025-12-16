#include <IBDSP/waveforms/sawtooth.hpp>
#include <IBDSP/waveforms/common.hpp>

#include <cmath>

namespace IBDSP::waveforms
{
    std::vector<float> generateSawtoothWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase,
        bool  descending
    )
    {
        std::vector<float> buffer(numSamples);

        const float phaseInc = TWO_PI * frequency / sampleRate;

        phase = std::fmod(phase, TWO_PI);
        if (phase < 0.0f) phase += TWO_PI;

        for (int i = 0; i < numSamples; ++i)
        {
            const float normPhase = phase / TWO_PI; // [0, 1)

            float value = descending
                ? (1.0f - 2.0f * normPhase)
                : (2.0f * normPhase - 1.0f);

            buffer[i] = amplitude * value;

            phase += phaseInc;
            if (phase >= TWO_PI)
                phase -= TWO_PI;
        }

        return buffer;
    }
}
