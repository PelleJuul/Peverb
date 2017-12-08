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
    // [31, 35, 113, 107, 374, 393]
    
    nestedAllpassLeft.addAllPass(0.089, 0.7);
    nestedAllpassLeft.addAllPass(0.071, 0.7);
    nestedAllpassLeft.addAllPass(0.0393, 0.7);
    nestedAllpassLeft.addAllPass(0.0107, 0.7);
    nestedAllpassLeft.addAllPass(0.0031, 0.7);
    
    nestedAllpassRight.addAllPass(0.083, 0.7);
    nestedAllpassRight.addAllPass(0.067, 0.7);
    nestedAllpassRight.addAllPass(0.0374, 0.7);
    nestedAllpassRight.addAllPass(0.0113, 0.7);
    nestedAllpassRight.addAllPass(0.0035, 0.7);
}

float LateReverb::processLeft(float t, float x)
{
    //float offset = (0.5 + sin(2 * M_PI * t * 1.1) * 0.5) * 0.0005;
    //nestedAllpassLeft.allPasses[2]->offset = offset;
    float result = nestedAllpassLeft.process(x);
    nestedAllpassRight.feedback = result;
    return result;
};

float LateReverb::processRight(float t, float x)
{
    //float offset = (0.5 + sin(2 * M_PI * t * 1.0) * 0.5) * 0.0005;
    //nestedAllpassRight.allPasses[2]->offset = offset;
    float result = nestedAllpassRight.process(x);
    nestedAllpassLeft.feedback = result;
    return result;
};

void LateReverb::setDecay(float value)
{
    nestedAllpassLeft.setGain(value);
    nestedAllpassRight.setGain(value);
}

void LateReverb::crossower()
{
    /*
    float feedbackLeft = nestedAllpassLeft.feedback;
    float feedbackRight = nestedAllpassRight.feedback;
    nestedAllpassLeft.feedback += feedbackRight * 0.2;
    nestedAllpassRight.feedback += feedbackLeft * 0.2;
    */
}
