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
    std::vector<float> buffer(1001);
    test.processBlock(buffer.data(), 1001);

    // TEST 1.1: 0/4 of the cycle should be 0
    assert(std::fabs(buffer[0]) - 0 < EPSILON);

    // TEST 1.2: 1/4 of the cycle should be 1
    assert(std::fabs(buffer[250]) - 1 < EPSILON);

    // TEST 1.3: 2/4 of the cycle should be 0
    assert(std::fabs(buffer[500]) - 0 < EPSILON);

    // TEST 1.4: 3/4 of the cycle should be 1
    assert(std::fabs(buffer[750]) - 1 < EPSILON);

    // TEST 1.5 4/4 of the cycle should be 0
    assert(std::fabs(buffer[1000]) - 0 < EPSILON);

    //TEST 1.6 reset() will return to 0

    test.reset();
    assert(test.process() < EPSILON);

    //TEST 1.7 modifying amplitude and frequency
    test.reset();
    test.setFrequency(2.0f);
    test.setAmplitude(10.0f);

    std::vector<float> buffer2(501); //samples per cycle = 1000/2 = 500
    test.processBlock(buffer2.data(), 501);

    assert(std::fabs(buffer2[0]) - 0 < EPSILON);

    assert(std::fabs(buffer2[125]) - 10 < EPSILON);

    assert(std::fabs(buffer2[250]) - 0 < EPSILON);

    assert(std::fabs(buffer2[375]) - 10 < EPSILON);

    assert(std::fabs(buffer2[500]) - 0 < EPSILON);

    //TEST 2: square wave

    IBDSP::oscillators::SquareOscillator sq;

    //one complete cycle takes up 1000 samples
    //TEST 2.1 standard sqare wave
    std::vector<float> testsq(1001);
    sq.processBlock(testsq.data(), 1001);
    for(int i = 0; i < 500; i++){
        assert(testsq[i] == 1);
    }
    for(int i = 500; i < 1001; i++){
        assert(testsq[i] == -1);
    }

    //TEST 2.2 75% duty cycle
    IBDSP::oscillators::SquareOscillator sq2(1.0f, 1.0f, 0.0, 1000.0f, 0.75f);
    std::vector<float> testsq2(1001);
    sq2.processBlock(testsq2.data(), 1001);
    for(int i = 0; i < 750; i++){
        assert(testsq2[i] == 1);
    }
    for(int i = 750; i < 1001; i++){
        assert(testsq2[i] == -1);
    }

    //TEST 2.3 high frequency switching
    IBDSP::oscillators::SquareOscillator sq3(10.0f, 44000.0f, 0.0f, 100000.0f, 0.5f);
    std::vector<float> testsq3(44000*10+1);
    sq3.processBlock(testsq3.data(), 44000*10+1);
    for(int i = 0; i < 440001; i++){
        assert(std::fabs(testsq3[i]) == 10.0f);
    }


}