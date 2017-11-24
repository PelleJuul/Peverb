/*
  ==============================================================================

    TestVerb.h
    Created: 24 Nov 2017 10:31:51am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Delay.h"
#include "TestAllPass.h"

class TestVerb
{
public:
    TestVerb();
    float process(float x);
    
private:
    TestAllPass allpassA;
    TestAllPass allpassB;
    TestAllPass allpassC;
    float gain = 0.5;
    float feedback;
};
