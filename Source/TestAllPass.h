/*
  ==============================================================================

    TestAllPass.h
    Created: 24 Nov 2017 12:31:43pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "delay.h"

class TestAllPass
{
public:
    TestAllPass(float delay, float gain);
    float process(float x);
    
private:
    Delay delay;
    float gain;
    float feedback;
};