/*
  ==============================================================================

    Chain.h
    Created: 8 Dec 2017 10:10:09am
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Processor.h"
#include <functional>

class Wrap : public Processor
{
public:
    Wrap(std::function<float(float)> processFunc);
    virtual float process(float x);
    
private:
    std::function<float(float)> processFunc;
};