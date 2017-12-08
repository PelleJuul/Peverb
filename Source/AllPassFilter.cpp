/*
  ==============================================================================

    AllpassFilter.cpp
    Created: 8 Dec 2017 9:00:03am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "AllpassFilter.h"

AllpassFilter::AllpassFilter(float delayLength, float gain, int sampleRate) :
    delay(delayLength, sampleRate)
{
    this->gain = gain;
}

float AllpassFilter::process(float x)
{
    float sum2 = delay.read() + -gain * x;
    float sum1 = gain * sum2 + x;
    delay.write(sum1);
    return sum2;
}