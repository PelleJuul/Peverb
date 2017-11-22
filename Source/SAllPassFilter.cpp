/*
  ==============================================================================

    SAllPass.cpp
    Created: 31 Oct 2017 12:51:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "SAllPassFilter.h"

SAllPassFilter::SAllPassFilter(int delay, float g) : delayLine()
{
    delayLine.setDelay(delay);
    this->g = g;
    this->delay = delay;
}

float SAllPassFilter::process(float x)
{
    float direct = x * (-g);
    float delayed = delayLine.read(delay);
    float sum2 = delayed * (1 - g * g) + direct;
    float sum1 = delayed * g + x;
    delayLine.write(sum1);
    return sum2;
}