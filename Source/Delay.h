/*
  ==============================================================================

    DelayLine.h
    Created: 30 Oct 2017 2:26:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "Node.h"
#include <vector>

class Delay : public Node
{
public:
    Delay(float seconds);
    void setDelay(float seconds);
    virtual float process(float t, float x) override;
    
    void write(float sample);
    float read();
private:
    int index;
    int size;
    std::vector<float> samples;
    
    
};
