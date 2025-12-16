#include <IBDSP/waveforms/sawtooth.hpp>

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

static constexpr float PI    = 3.14159265358979323846f;
static constexpr float TWOPI = 6.2831853071795864769f;
static constexpr float EPS   = 1e-5f;

int main() {

    float amplitude  = 1.0f;
    float frequency  = 480.0f;     // divides sampleRate exactly
    float sampleRate = 48000.0f;
    int   numSamples = 48000;

    // -------------------------------------------------
    // Test 1: Correct buffer size
    // -------------------------------------------------
    auto saw = IBDSP::waveforms::generateSawtoothWave(
        amplitude, frequency, sampleRate, numSamples
    );

    assert(saw.size() == static_cast<size_t>(numSamples));

    // -------------------------------------------------
    // Test 2: Range check [-1, 1]
    // -------------------------------------------------
    float minVal =  1.0f;
    float maxVal = -1.0f;

    for (float s : saw) {
        minVal = std::min(minVal, s);
        maxVal = std::max(maxVal, s);
    }

    assert(minVal >= -1.0f - EPS);
    assert(maxVal <=  1.0f + EPS);

    // -------------------------------------------------
    // Test 3: First sample at zero phase (ascending)
    // phase = 0 → value ≈ -1
    // -------------------------------------------------
    assert(std::abs(saw[0] + 1.0f) < EPS);

    // -------------------------------------------------
    // Test 4: Linear ramp over one period
    // -------------------------------------------------
    int samplesPerPeriod = static_cast<int>(sampleRate / frequency);
    float expectedSlope = 2.0f / samplesPerPeriod;

    for (int i = 1; i < samplesPerPeriod; ++i) {
        float diff = saw[i] - saw[i - 1];
        assert(std::abs(diff - expectedSlope) < 1e-4f);
    }

    // -------------------------------------------------
    // Test 5: Periodicity (two periods match)
    // -------------------------------------------------
    auto twoPeriods = IBDSP::waveforms::generateSawtoothWave(
        amplitude, frequency, sampleRate, 2 * samplesPerPeriod
    );

    for (int i = 0; i < samplesPerPeriod; ++i) {
        assert(std::abs(twoPeriods[i] - twoPeriods[i + samplesPerPeriod]) < 1e-4f);
    }

    // -------------------------------------------------
    // Test 6: Descending sawtooth
    // -------------------------------------------------
    auto sawDesc = IBDSP::waveforms::generateSawtoothWave(
        amplitude, frequency, sampleRate, samplesPerPeriod, 0.0f, true
    );

    // First sample descending should start near +1
    assert(std::abs(sawDesc[0] - 1.0f) < EPS);

    // Should be decreasing
    for (int i = 1; i < samplesPerPeriod; ++i) {
        assert(sawDesc[i] < sawDesc[i - 1] + EPS);
    }

    // -------------------------------------------------
    // Test 7: Phase shift (π)
    // -------------------------------------------------
    auto sawShifted = IBDSP::waveforms::generateSawtoothWave(
        amplitude, frequency, sampleRate, 1, PI
    );

    // phase = π → norm = 0.5 → value ≈ 0
    assert(std::abs(sawShifted[0]) < 1e-4f);

    std::cout << "All sawtooth wave tests passed!\n";
    return 0;
}
