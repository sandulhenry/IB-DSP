#include <iostream>
#include <fstream>
#include <complex>
#include <string>
#include <IBDSP/headers.hpp>

template<typename T>
void writeVector(std::ofstream& outfile, const std::vector<T>& vec){
    for(int i = 0; i < vec.size(); i++){
        outfile << vec[i] << ',';
    }

    outfile << std::endl;
} 

template<typename T>
void writeVector(std::ofstream& outfile, const std::vector<std::complex<T>>& vec){
    for(int i = 0; i < vec.size(); i++){
        outfile << vec[i].real() << ',';
    }

    outfile << std::endl;
} 

int main(int argc, char** argv){
    //only type the argument for file path ending in .../data.csv
    //only trying to clear it
    const std::string stringout = (argc == 2) ? argv[1] : "data.csv";
    std::ofstream outputFile(stringout, std::ios::trunc);

    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the file " << stringout << std::endl;
        return 1;
    }

    outputFile.close();

    outputFile.open(stringout, std::ios::app);

    std::vector<float> vec = IBDSP::waveforms::generateSineWave(1,1,100,pow(2,15));
    
    //FIRST LINE: time domain sine wave, frequency of 1, amplitude of 1
    writeVector(outputFile, vec);

    std::vector<std::complex<double>> vec2 = IBDSP::vecToComplex(vec);

    IBDSP::fft(vec2, false);

    //SECOND LINE: frequency domain, two peaks
    writeVector(outputFile, vec2);

    IBDSP::fft(vec2, true);
    //THIRD LINE: time domain sine wave, frequency of 1, amplitude of 1
    writeVector(outputFile, vec2);

}