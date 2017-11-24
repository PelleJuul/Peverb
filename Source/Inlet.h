/*
  ==============================================================================

    Inlet.h
    Created: 22 Nov 2017 9:29:33pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "Node.h"

class Inlet : public Node
{
public:
    virtual float process(float t, float x) override;
};