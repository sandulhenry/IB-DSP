#pragma once

#include <IBDSP/oscillators/oscillator.hpp>

namespace IBDSP::oscillators
{
    class SawtoothOscillator : public Oscillator
    {
    public:
        SawtoothOscillator(
            float amplitude = 1.0f,
            float frequency = 1.0f,
            double phase = 0.0f,
            float sampleRate = 1000.0f
        );

        void setFrequency(float frequency) override;
        void setSampleRate(float sampleRate) override;
        void setAmplitude(float amp) override;

        float process() override;
        void reset(double phase = 0.0f) override;

    private:
        void updatePhaseIncrement();

        float mAmplitude;
        float mFrequency;
        double mPhase;
        float mSampleRate;
        float mPhaseInc;
    };
}
