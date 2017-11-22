/*
  ==============================================================================

    AllPassFilter.cpp
    Created: 30 Oct 2017 2:26:37pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "AllPassFilter.h"
#include "DelayLine.h"
#include <math.h>

AllPassFilter::AllPassFilter(float delay, float g) : delayLine()
{
    delayLine.setDelay(delay);
    scale = 1.0;
    this->g = g;
    this->delay = delay;
}

float AllPassFilter::process(float x)
{
    float direct = x * (-g);
    float sum2 = delayLine.read(delay * scale) + direct;
    float sum1 = sum2 * g + x;
    delayLine.write(sum1);
    return sum2;
}