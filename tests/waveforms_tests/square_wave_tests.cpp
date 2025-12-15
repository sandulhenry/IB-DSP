#include <IBDSP/waveforms/square.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    const float pi = 3.14159265358979323846f;

    // Parameters
    float frequency = 480.0f;       // divides sampleRate exactly
    float sampleRate = 48000.0f;
    int numSamples = 48000;
    float phaseShift = 0.0f;

    // -------------------------------
    // Test 1: 50% duty square wave
    // -------------------------------
    auto square50 = IBDSP::waveforms::generateSquareWave(1.0, frequency, sampleRate, numSamples, phaseShift, 0.5f);
    assert(square50.size() == static_cast<size_t>(numSamples));

    float maxVal = -1.0f;
    float minVal = 1.0f;
    for (auto s : square50) {
        if (s > maxVal) maxVal = s;
        if (s < minVal) minVal = s;
    }
    assert(maxVal <= 1.0f && maxVal >= 0.99f);
    assert(minVal >= -1.0f && minVal <= -0.99f);

    // -------------------------------
    // Test 2: Duty cycle correctness
    // -------------------------------
    int samplesPerPeriod = static_cast<int>(sampleRate / frequency);
    int highCount = 0;
    for (int i = 0; i < samplesPerPeriod; ++i) {
        if (square50[i] > 0.0f) highCount++;
    }
    float dutyMeasured = static_cast<float>(highCount) / samplesPerPeriod;
    assert(std::abs(dutyMeasured - 0.5f) < 1e-6f);

    // -------------------------------
    // Test 3: Phase shift
    // -------------------------------
    auto squareShifted = IBDSP::waveforms::generateSquareWave(1.0, frequency, sampleRate, 1, pi/2, 0.5f);
    // phase shift of pi/2 should put first sample in high region
    assert(squareShifted[0] > 0.0f);

    // -------------------------------
    // Test 4: Custom duty cycle
    // -------------------------------
    float duty = 0.25f;
    auto square25 = IBDSP::waveforms::generateSquareWave(1.0, frequency, sampleRate, samplesPerPeriod, 0.0f, duty);

    highCount = 0;
    for (int i = 0; i < samplesPerPeriod; ++i) {
        if (square25[i] > 0.0f) highCount++;
    }
    dutyMeasured = static_cast<float>(highCount) / samplesPerPeriod;
    assert(std::abs(dutyMeasured - duty) < 1e-6f);

    //Test 5: amplitude is accurate
    numSamples = 10000;
    auto squareA = IBDSP::waveforms::generateSquareWave(
        1.0,
        frequency, 
        sampleRate,
        numSamples,
        0.0f,
        duty
    );

    auto squareB = IBDSP::waveforms::generateSquareWave(
        2.0,
        frequency, 
        sampleRate,
        numSamples,
        0.0f,
        duty
    );

    for(int i = 0; i < samplesPerPeriod; i++){
        assert(squareB[i] == (squareA[i] * 2));
    }

    std::cout << "All square wave tests passed!\n";
    return 0;
}
