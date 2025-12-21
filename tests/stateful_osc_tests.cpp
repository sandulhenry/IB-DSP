#include <IBDSP/oscillators/sine_osc.hpp>
#include <IBDSP/oscillators/sawtooth_osc.hpp>
#include <IBDSP/oscillators/square_osc.hpp>

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

static constexpr float EPSILON = 1e-2f;

/* 
    NOTE: 
    samples per cycle = sample rate / wavefrom frequnecy 

    for example, for the default sine wave, there are 1000/1 samples per cycle. 
*/
int main(){
    
    // 1. sine wave tests

    IBDSP::oscillators::SineOscillator test;
    //test processing the whole block
    std::vector<float> buffer(1000);
    test.processBlock(buffer.data(), 1000);

    // TEST 1.1: 0/4 of the cycle should be 0
    assert(std::fabs(buffer[0]) - 0 < EPSILON);

    // TEST 1.2: 1/4 of the cycle should be 1
    assert(std::fabs(buffer[250-1]) - 1 < EPSILON);

    // TEST 1.3: 2/4 of the cycle should be 0
    assert(std::fabs(buffer[500-1]) - 0 < EPSILON);

    // TEST 1.4: 3/4 of the cycle should be 1
    assert(std::fabs(buffer[750 - 1]) - 1 < EPSILON);

    // TEST 1.5 4/4 of the cycle should be 0
    assert(std::fabs(buffer[1000-1]) - 0 < EPSILON);

    //TEST 1.6 reset() will return to 0

    test.reset();
    assert(test.process() < EPSILON);


}