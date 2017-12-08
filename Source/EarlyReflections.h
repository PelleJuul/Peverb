/*
  ==============================================================================

    EarlyReflections.h
    Created: 26 Nov 2017 5:50:14pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "DelayLine.h"
#include <vector>

class EarlyReflections
{
public:
    float left;
    float right;
    
    EarlyReflections();
    float process(float x);

private:
    float directGain = 0.5;
    float reflectGain = 0.5;
    DelayLine delay;
    std::vector<float> tabsLeft;
    std::vector<float> tabsRight;
    std::vector<float> coeffsLeft;
    std::vector<float> coeffsRight;
    IIRFilter binauralLowPassLeft;
    IIRFilter binauralLowPassRight;
    DelayLine binauralDelayLeft;
    DelayLine binauralDelayRight;
};
