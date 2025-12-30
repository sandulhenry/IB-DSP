#include <IBDSP/oscillators/square_osc.hpp>
#include <IBDSP/common.hpp>

namespace IBDSP::oscillators
{
    SquareOscillator::SquareOscillator(
        float amplitude,
        float frequency,
        double phase,
        float sampleRate,
        float duty
    )
        : mAmplitude(amplitude),
          mFrequency(frequency),
          mPhase(phase),
          mSampleRate(sampleRate),
          mDuty(duty)
    {
        updatePhaseIncrement();
    }

    void SquareOscillator::setFrequency(float frequency)
    {
        mFrequency = frequency;
        updatePhaseIncrement();
    }

    void SquareOscillator::setSampleRate(float sampleRate)
    {
        mSampleRate = sampleRate;
        updatePhaseIncrement();
    }

    void SquareOscillator::setAmplitude(float amp)
    {
        mAmplitude = amp;
    }

    void SquareOscillator::setDutyCycle(float duty)
    {
        // Clamp to safe range
        if (duty < 0.01f) duty = 0.01f;
        if (duty > 0.99f) duty = 0.99f;
        mDuty = duty;
    }

    float SquareOscillator::process()
    {
        float normPhase = mPhase / TWO_PI;

        float out = (normPhase < mDuty ? 1.0f : -1.0f) * mAmplitude;

        mPhase += mPhaseInc;
        if (mPhase >= TWO_PI)
            mPhase -= TWO_PI;

        return out;
    }

    void SquareOscillator::reset(double phase)
    {
        mPhase = phase;
    }

    void SquareOscillator::updatePhaseIncrement()
    {
        mPhaseInc = TWO_PI * mFrequency / mSampleRate;
    }
}
