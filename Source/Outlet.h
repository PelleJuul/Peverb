/*
  ==============================================================================

    Outlet.h
    Created: 22 Nov 2017 9:28:38pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once

#include "Node.h"

class Outlet : public Node
{
public:
    virtual float process(float t, float x) override;
    float run(float t, float x);
};