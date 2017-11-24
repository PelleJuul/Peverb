/*
  ==============================================================================

    TestAllPass.cpp
    Created: 24 Nov 2017 12:31:43pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "TestAllPass.h"
#include "delay.h"

TestAllPass::TestAllPass(float delay, float gain) : delay(delay)
{
    this->gain = gain;
}

float TestAllPass::process(float x)
{
    float inSum = x + feedback * (-gain);
    float delayed = delay.read();
    delay.write(inSum);
    float outSum = delayed + x * gain;
    
    feedback = outSum;
    return outSum;
}