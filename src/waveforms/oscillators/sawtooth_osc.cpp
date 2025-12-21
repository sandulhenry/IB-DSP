#include <IBDSP/oscillators/sawtooth_osc.hpp>
#include <IBDSP/common.hpp>

namespace IBDSP::oscillators
{
    SawtoothOscillator::SawtoothOscillator(
        float amplitude,
        float frequency,
        float phase,
        float sampleRate)
        : mAmplitude(amplitude),
          mFrequency(frequency),
          mPhase(phase),
          mSampleRate(sampleRate)
    {
        updatePhaseIncrement();
    }

    void SawtoothOscillator::setFrequency(float frequency)
    {
        mFrequency = frequency;
        updatePhaseIncrement();
    }

    void SawtoothOscillator::setSampleRate(float sampleRate)
    {
        mSampleRate = sampleRate;
        updatePhaseIncrement();
    }

    void SawtoothOscillator::setAmplitude(float amp)
    {
        mAmplitude = amp;
    }

    float SawtoothOscillator::process()
    {
        // Normalize phase to [0, 1)
        float normPhase = mPhase / TWO_PI;

        // Bipolar sawtooth [-1, 1)
        float out = (2.0f * normPhase - 1.0f) * mAmplitude;

        mPhase += mPhaseInc;
        if (mPhase >= TWO_PI)
            mPhase -= TWO_PI;

        return out;
    }

    void SawtoothOscillator::reset(float phase)
    {
        mPhase = phase;
    }

    void SawtoothOscillator::updatePhaseIncrement()
    {
        mPhaseInc = TWO_PI * mFrequency / mSampleRate;
    }
}
