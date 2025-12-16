#include <IBDSP/waveforms/square.hpp>
#include <IBDSP/waveforms/common.hpp>

#include <cmath>
#include <algorithm>

namespace IBDSP::waveforms
{
    std::vector<float> generateSquareWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int   numSamples,
        float phase,
        float duty
    )
    {
        std::vector<float> buffer(numSamples);

        duty = std::clamp(duty, 0.0f, 1.0f);

        const float phaseInc = TWO_PI * frequency / sampleRate;

        phase = std::fmod(phase, TWO_PI);
        if (phase < 0.0f) phase += TWO_PI;

        for (int i = 0; i < numSamples; ++i)
        {
            const float normPhase = phase / TWO_PI;

            buffer[i] = (normPhase < duty ? amplitude : -amplitude);

            phase += phaseInc;
            if (phase >= TWO_PI)
                phase -= TWO_PI;
        }

        return buffer;
    }
}
