#pragma once

#include <cstddef>
#include <vector>

using namespace std;

namespace IBDSP::waveforms {
    
    vector<float> generateSquareWave(
        float amplitude,
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift = 0.0f,
        float duty = 0.5f
    );
}