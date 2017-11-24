/*
  ==============================================================================

    Chain.h
    Created: 23 Nov 2017 2:16:13pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include "Node.h"

class Node;

class Chain
{
public:
    Node *last;
    Node *first;
    Chain operator>(Chain &chain);
    Chain operator>(Node &node);
    Node& operator>>(Node &node);
};