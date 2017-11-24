/*
  ==============================================================================

    Gain.h
    Created: 22 Nov 2017 9:25:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "Node.h"

class Gain : public Node
{
public:
    Gain(float initGain);
    float process(float t, float x) override;
    void setGain(float value);
    
private:
    float gain;
};