/*
  ==============================================================================

    Sum.h
    Created: 22 Nov 2017 9:02:21pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Node.h"

class Sum : public Node
{
public:
    virtual float process(float t, float x) override;
};
