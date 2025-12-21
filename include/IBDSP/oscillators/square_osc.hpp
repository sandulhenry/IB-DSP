#pragma once

#include <IBDSP/oscillators/oscillator.hpp>

namespace IBDSP::oscillators
{
    class SquareOscillator : public Oscillator
    {
    public:
        SquareOscillator(
            float amplitude = 1.0f,
            float frequency = 1.0f,
            float phase = 0.0f,
            float sampleRate = 1000.0f,
            float duty = 0.5f
        );

        void setFrequency(float frequency) override;
        void setSampleRate(float sampleRate) override;
        void setAmplitude(float amp) override;

        // Square-specific
        void setDutyCycle(float duty);

        float process() override;
        void reset(float phase = 0.0f) override;

    private:
        void updatePhaseIncrement();

        float mAmplitude;
        float mFrequency;
        float mPhase;
        float mSampleRate;
        float mPhaseInc;
        float mDuty;   // 0.0–1.0
    };
}
