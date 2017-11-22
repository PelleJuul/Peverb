/*
  ==============================================================================

    NestedAllPass.cpp
    Created: 31 Oct 2017 12:32:24pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "NestedAllPass.h"
#include "AllPassFilter.h"

NestedAllPass::NestedAllPass(float g)
{
    this->g = g;
    lastY = 0;
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
    float direct = x * (-g);
    
    float sum2 = x + lastY * g;
    float allPassed = sum2;
    
    for (AllPassFilter *ap : allPasses) {
        allPassed = ap->process(allPassed);
    }
    
    float sum1 = direct + allPassed;
    lastY = sum1;
    return sum1;
}