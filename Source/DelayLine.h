/*
  ==============================================================================

    DelayLine.h
    Created: 30 Oct 2017 2:26:22pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include <vector>

class DelayLine
{
public:
    DelayLine();
    void setDelay(float newSize);
    void setDelaySeconds(float newSize);
    void write(float sample);
    float read(float t) const;
    void clear();
    
private:
    int index;
    float sampleRate;
    std::vector<float> samples;
};
