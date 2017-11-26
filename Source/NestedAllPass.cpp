/*
  ==============================================================================

    NestedAllPass.cpp
    Created: 31 Oct 2017 12:32:24pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "NestedAllPass.h"
#include "AllPassFilter.h"

NestedAllPass::NestedAllPass() : NestedAllPass(0.2)
{
    
}

NestedAllPass::NestedAllPass(float g)
{
    this->g = g;
    feedback = 0;
    IIRCoefficients coeffA = IIRCoefficients::makeLowPass(44100, 2000, 0.2);
    feedbackFilter.setCoefficients(coeffA);
    IIRCoefficients coeffB = IIRCoefficients::makeLowPass(44100, 8000, 0.5);
    inputFilter.setCoefficients(coeffB);
}

void NestedAllPass::addAllPass(float delay, float g)
{
    AllPassFilter *ap = new AllPassFilter(delay, g);
    allPasses.push_back(ap);
}

void NestedAllPass::setScale(float scale)
{
    for (AllPassFilter *ap : allPasses) {
        ap->setScale(scale);
    }
}

void NestedAllPass::setInnerGain(float gain)
{
    for (auto *ap : allPasses) {
        ap->setGain(gain);
    }
}

void NestedAllPass::setGain(float gain)
{
    g = gain;
}

float NestedAllPass::process(float x)
{
    float filtered = inputFilter.processSingleSampleRaw(x);
    float direct = filtered * (-g);
    float sum2 = x + feedback;
    float allPassed = sum2;
    
    for (AllPassFilter *ap : allPasses) {
        allPassed = ap->process(allPassed);
    }
    
    float sum1 = direct + allPassed;
    feedback = feedbackFilter.processSingleSampleRaw(sum1) * g;
    return sum1;
}