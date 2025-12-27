#include "IBDSP/FTs/fft.hpp"
#include "IBDSP/waveforms/sine.hpp"

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <random>

int main()
{
    std::vector<float> ref = IBDSP::waveforms::generateSineWave(1, 1000, 4000, 8192, 0.0f);
    std::vector<std::complex<double>> test;

    for (int i = 0; i < (int)ref.size(); i++)
    {
        test.push_back(std::complex<double>(ref[i], 0));
    }

    std::vector<std::complex<double>> test_2 = test;

    std::cout << "making ffts" << std::endl;

    IBDSP::fft(test_2, false);
    IBDSP::fft(test_2, true);

    constexpr double eps = 1e-9;

    for (int i = 0; i < (int) test.size(); ++i)
    {
        assert(std::abs(test[i] - test_2[i]) < eps);
    }

    return 0;
}