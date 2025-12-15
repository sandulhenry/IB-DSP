#include <IBDSP/waveforms/sine.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm> // for std::max_element

const float pi = 3.14159265358979323846f;
const float epsilon = 1e-6f; // tolerance for floating-point comparisons

int main()
{
    // Parameters
    float frequency = 440.0f;
    float sampleRate = 48000.0f;
    int numSamples = 48000;
    float phaseShift = 0.0f;

    auto buffer = IBDSP::waveforms::generateSineWave(frequency, sampleRate, numSamples, phaseShift);

    // ---- BASIC TESTS ----

    // Test 1: Correct size
    assert(buffer.size() == static_cast<size_t>(numSamples));

    // Test 2: First sample with zero phase shift should be ~0
    assert(std::abs(buffer[0]) < epsilon);

    // Test 3: Max amplitude should be <= 1
    float maxVal = *std::max_element(buffer.begin(), buffer.end(), [](float a, float b)
                                     { return std::abs(a) < std::abs(b); });
    assert(maxVal <= 1.0f);

    // Test 4: Phase shift works (sin(pi) ≈ 0)
    auto shiftedBuffer = IBDSP::waveforms::generateSineWave(frequency, sampleRate, 1, pi);
    //std::cout << "DEBUG: val at idx 0: " << shiftedBuffer[0] << std::endl;
    assert(std::abs(shiftedBuffer[0]) < epsilon);

    // ---- ADDITIONAL TESTS ----

    // Test 5: One full period ends at approx zero
    int samplesPerPeriod = static_cast<int>(sampleRate / frequency);
    auto periodBuffer = IBDSP::waveforms::generateSineWave(frequency, sampleRate, samplesPerPeriod, 0.0f);
    //std::cout << "DEBUG: val at idx back: " << periodBuffer.back() << std::endl;
    assert(std::abs(periodBuffer.back()) < 0.1f); // allow small epsilon for float rounding

    // Test 6: Two periods repeat (frequency divides sampleRate exactly)
    float exactFreq = 480.0f; // 48000 / 480 = 100 samples per period exactly
    int exactSamplesPerPeriod = static_cast<int>(sampleRate / exactFreq);
    auto twoPeriodBufferExact = IBDSP::waveforms::generateSineWave(exactFreq, sampleRate, 2 * exactSamplesPerPeriod, 0.0f);

    // Compare the two periods
    for (int i = 0; i < exactSamplesPerPeriod; ++i)
    {
        cout << twoPeriodBufferExact[i] - twoPeriodBufferExact[i + exactSamplesPerPeriod] << endl;
        assert(std::abs(twoPeriodBufferExact[i] - twoPeriodBufferExact[i + exactSamplesPerPeriod]) < 1e-5f);
    }

    // Test 7: Negative frequency behaves correctly (phase flips)
    auto negFreqBuffer = IBDSP::waveforms::generateSineWave(-frequency, sampleRate, 100, 0.0f);
    for (size_t i = 0; i < 100; ++i)
    {
        assert(std::abs(negFreqBuffer[i] + buffer[i]) < 1e-4f); // sine(-x) = -sin(x)
    }

    // Test 8: Very small frequency produces near-zero slope over first few samples
    auto tinyFreqBuffer = IBDSP::waveforms::generateSineWave(0.01f, sampleRate, 100, 0.0f);
    assert(std::abs(tinyFreqBuffer[1] - tinyFreqBuffer[0]) < 1e-5f);

    std::cout << "All tests passed!\n";
    return 0;
}
