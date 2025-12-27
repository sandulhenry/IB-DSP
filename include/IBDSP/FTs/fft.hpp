#pragma once
#include <complex>
#include <vector>

//credits to https://cp-algorithms.com/algebra/fft.html

namespace IBDSP{

    void fft(std::vector<std::complex<double>> & a, bool invert);
}