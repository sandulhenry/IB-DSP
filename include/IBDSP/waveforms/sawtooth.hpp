#pragma once

#include <vector>

using namespace std;

namespace IBDSP::waveforms {
    
    // assume ascending by default
    vector<float> generateSawtoothWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift = 0.0f,
        bool desc = false
    );

}