/*
  ==============================================================================

    Node.h
    Created: 22 Nov 2017 8:39:15pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#pragma once
#include <vector>
#include "Chain.h"

class Chain;

class Node
{
public:
    virtual ~Node() {};
    void connect(Node &other);
    virtual float process(float t, float x) = 0;
    float alone(float t, float x);
    float first(float t, float x);
    float sumConnections(float t, float x);
    void prepare();
    virtual bool wasVisited();
    void begin();
    float finish(float output);
    void operator>>= (Node &other);
    Node &operator>>(Node &other);
    Node &operator>>(Chain &other);
    Chain operator>(Node &other);
    Chain operator>(Chain &chain);
    
protected:
    std::vector<Node*> visitedNodes;
    void prepareInner(std::vector<Node*> *visitedNodes);
    bool visited;
    float lastOutput;
    std::vector<Node*> connected;
};