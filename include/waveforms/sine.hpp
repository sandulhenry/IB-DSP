#pragma once

#include <cstddef>
#include <vector>

using namespace std;

namespace IBDSP::waveforms {

class SineWave {
public:
    SineWave();

    // Set sample rate (must be called before processing)
    void setSampleRate(float sampleRate);

    // Set wave frequency in Hz
    void setFrequency(float frequency);

    // Reset phase to 0
    void reset();

    // Generate one sample
    float process();

    vector<float> waveVector();

private:
    float sampleRate_ { 44100.0f };
    float frequency_  { 440.0f };
    float phase_      { 0.0f };
    float phaseInc_   { 0.0f };

    void updatePhaseIncrement();
};

} 
