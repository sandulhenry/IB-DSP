#include <IBDSP/oscillators/sine_osc.hpp>
#include <IBDSP/common.hpp>
#include <cmath>

namespace IBDSP::oscillators
{
    SineOscillator::SineOscillator(
        float amplitude,
        float frequency,
        double phase,
        float sampleRate)
        : mAmplitude(amplitude),
          mFrequency(frequency),
          mPhase(phase),
          mSampleRate(sampleRate)
    {
        updatePhaseIncrement();
    }

    void SineOscillator::setFrequency(float frequency)
    {
        mFrequency = frequency;
        updatePhaseIncrement();
    }

    void SineOscillator::setSampleRate(float sampleRate)
    {
        mSampleRate = sampleRate;
        updatePhaseIncrement();
    }

    void SineOscillator::setAmplitude(float amp)
    {
        mAmplitude = amp;
    }

    float SineOscillator::process()
    {
        float out = std::sin(mPhase) * mAmplitude;

        mPhase += mPhaseInc;
        if (mPhase >= TWO_PI)
            mPhase -= TWO_PI;

        return out;
    }

    void SineOscillator::reset(double phase)
    {
        mPhase = phase;
    }

    void SineOscillator::updatePhaseIncrement()
    {
        mPhaseInc = TWO_PI * mFrequency / mSampleRate;
    }
}
