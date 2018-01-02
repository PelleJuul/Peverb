/*
  ==============================================================================

    AllpassFilter.h
    Created: 8 Dec 2017 9:00:03am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Processor.h"
#include "Delay.h"

class AllpassFilter : public Processor
{
public:
    AllpassFilter(float delayLength, float gain, int sampleRate);
    float process(float x) override;
    
    float delayLength;
    float delayOffset;
private:
    Delay delay;
    float gain;
    float lastY;
};
