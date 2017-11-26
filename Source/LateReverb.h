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
    float processLeft(float x);
    float processRight(float x);
    void crossower();
    
private:
    NestedAllPass nestedAllpassLeft;
    NestedAllPass nestedAllpassRight;
};