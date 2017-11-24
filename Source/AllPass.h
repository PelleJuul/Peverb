/*
  ==============================================================================

    AllPassFilter.h
    Created: 30 Oct 2017 2:26:37pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "Inlet.h"
#include "Outlet.h"
#include "Delay.h"
#include "Node.h"
#include "Gain.h"
#include "Sum.h"

class Allpass : public Node
{
public:
    Allpass(float delay, float gain);
    virtual float process(float t, float x) override;
    
private:
    Inlet inlet;
    Outlet outlet;
    Sum inSum;
    Sum outSum;
    Delay delay;
    Gain outGain;
    Gain directGain;
    Gain feedbackGain;
};