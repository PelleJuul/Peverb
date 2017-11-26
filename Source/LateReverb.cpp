/*
  ==============================================================================

    LateReverb.cpp
    Created: 24 Nov 2017 1:35:00pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "LateReverb.h"

LateReverb::LateReverb()
{
    // [10, 19,  37, 39,  67, 71, 83, 89, 119, 121]
    
    nestedAllpassLeft.addAllPass(0.121, 0.7);
    nestedAllpassLeft.addAllPass(0.089, 0.7);
    nestedAllpassLeft.addAllPass(0.071, 0.7);
    nestedAllpassLeft.addAllPass(0.039, 0.7);
    nestedAllpassLeft.addAllPass(0.019, 0.7);
    
    nestedAllpassRight.addAllPass(0.119, 0.7);
    nestedAllpassRight.addAllPass(0.083, 0.7);
    nestedAllpassRight.addAllPass(0.067, 0.7);
    nestedAllpassRight.addAllPass(0.037, 0.7);
    nestedAllpassRight.addAllPass(0.010, 0.7);
}

float LateReverb::processLeft(float x)
{
    float result = nestedAllpassLeft.process(x);
    return result;
};

float LateReverb::processRight(float x)
{
    float result = nestedAllpassRight.process(x);
    return result;
};

void LateReverb::crossower()
{
    float feedbackLeft = nestedAllpassLeft.feedback;
    float feedbackRight = nestedAllpassRight.feedback;
    nestedAllpassLeft.feedback += feedbackRight * 0.2;
    nestedAllpassRight.feedback += feedbackLeft * 0.2;
}
