/*
  ==============================================================================

    NestedAllPass.h
    Created: 31 Oct 2017 12:32:24pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "AllPassFilter.h"

class NestedAllPass
{
public:
    NestedAllPass(float g);
    void addAllPass(float delay, float g);
    float process(float x);
    
    void setScale(float scale);
    void setInnerGain(float newVal);
    void setGain(float value);
    
private:
    float g;
    float lastY;
    std::vector<AllPassFilter*> allPasses;
};