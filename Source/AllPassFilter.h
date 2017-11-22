/*
  ==============================================================================

    AllPassFilter.h
    Created: 30 Oct 2017 2:26:37pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "DelayLine.h"

class AllPassFilter
{
public:
    AllPassFilter(float delay, float g);
    float process(float x);
    void setScale(float newScale) { scale = newScale; };
    void setGain(float value) { g = value; };
    
private:
    float g;
    float scale;
    float delay;
    DelayLine delayLine;
};