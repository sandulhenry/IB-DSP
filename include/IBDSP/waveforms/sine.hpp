#pragma once

#include <cstddef>
#include <vector>

using namespace std;

namespace IBDSP::waveforms {

    vector<float> generateSineWave(
        float frequency,
        float sampleRate,
        int numSamples,
        float phase_shift
    );

    
};
