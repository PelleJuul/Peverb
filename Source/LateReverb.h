/*
  ==============================================================================

    LateReverb.h
    Created: 24 Nov 2017 1:35:00pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "NestedAllpass.h"

class LateReverb
{
public:
    LateReverb();
    float processLeft(float t, float x);
    float processRight(float t, float x);
    void crossower();
    void setDecay(float value);
    
private:
    NestedAllPass nestedAllpassLeft;
    NestedAllPass nestedAllpassRight;
};