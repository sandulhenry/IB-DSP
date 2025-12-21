#pragma once

namespace IBDSP::oscillators
{
    class Oscillator
    {
    public:
        virtual ~Oscillator() = default;

        virtual void setFrequency(float frequency) = 0;
        virtual void setSampleRate(float sampleRate) = 0;
        virtual void setAmplitude(float amp) = 0;
        virtual float process() = 0;
        virtual void reset(float phase = 0.0f) = 0;

        // helper
        void processBlock(float* buffer, int numSamples)
        {
            for (int i = 0; i < numSamples; ++i)
                buffer[i] = process();
        }
    };
}
