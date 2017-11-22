/*
  ==============================================================================

    SAllPass.h
    Created: 31 Oct 2017 12:51:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "DelayLine.h"

class SAllPassFilter
{
public:
    SAllPassFilter(int delay, float g);
    float process(float x);
    
private:
    float g;
    int delay;
    DelayLine delayLine;
};