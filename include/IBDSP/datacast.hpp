#pragma once
#include <complex>
#include <cmath>
#include <vector>

namespace IBDSP
{
    /*
     * take any type of input vector and return an equal complex<double> vector
     * this is required for our implentation of FFT
     *
     */
    template <typename T>
    std::vector<std::complex<double>> vecToComplex(const std::vector<T> &og)
    {
        std::vector<std::complex<double>> toreturn;

        for (int i = 0; i < (int)og.size(); i++)
        {
            toreturn.push_back(std::complex<double>(og[i], 0));
        }

        return toreturn;
    }
}