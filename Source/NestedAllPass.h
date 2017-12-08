/*
  ==============================================================================

    NestedAllPass.h
    Created: 31 Oct 2017 12:32:24pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AllPassFilter.h"
#include "DelayLine.h"

class NestedAllPass
{
public:
    float feedback;
    
    NestedAllPass();
    NestedAllPass(float g);
    void addAllPass(float delay, float g);
    float process(float x);
    
    void setScale(float scale);
    void setInnerGain(float newVal);
    void setGain(float value);
    
    std::vector<AllPassFilter*> allPasses;
private:
    float g;
    DelayLine delay;
    IIRFilter feedbackFilter;
    IIRFilter inputFilter;
};