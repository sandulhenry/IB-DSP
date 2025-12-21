#include <IBDSP/oscillators/sine_osc.hpp>
#include <IBDSP/oscillators/sawtooth_osc.hpp>
#include <IBDSP/oscillators/square_osc.hpp>

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>

static constexpr float SAMPLE_RATE = 48000.0f;
static constexpr float EPSILON = 1e-4f;

/* 
    NOTE: 
    samples per cycle = sample rate / wavefrom frequnecy 

    for example, for the default sine wave, there are 1000/1 samples per cycle. 
*/
int main(){
    
    // sine wave tests

    IBDSP::oscillators::SineOscillator test;

    //initally 0
    assert(std::fabs(test.process()) <= EPSILON);

    /* A qaurter of the way through the cycle, we should ~1 */

    std::vector<float> buffer (250-1);
    test.processBlock(buffer.data(), 250-1);

    std::cout << "BUFFER BACK is " << buffer.back() << std::endl;

    assert(std::fabs(buffer.back() - 1) < EPSILON);

    
}