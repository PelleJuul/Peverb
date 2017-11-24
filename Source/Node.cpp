/*
  ==============================================================================

    Node.cpp
    Created: 22 Nov 2017 8:39:15pm
    Author:  Pelle Juul Christensen

  ==============================================================================
*/

#include "Node.h"
#include "Inlet.h"
#include "Outlet.h"
#include <vector>
#include <algorithm>

class Inlet;

void Node::connect(Node &other)
{
    other.connected.push_back(this);
}

void Node::prepare()
{
    visitedNodes.clear();
    prepareInner(&visitedNodes);
}

void Node::prepareInner(std::vector<Node*> *visitedNodes)
{
    if (std::find(visitedNodes->begin(), visitedNodes->end(), this) != visitedNodes->end()) {
        return;
    }
    
    visitedNodes->push_back(this);
    visited = false;
    
    for (Node *node : connected) {
        node->prepareInner(visitedNodes);
    }
}

float Node::alone(float t, float x)
{
    std::vector<Node*> wasConnected = connected;
    connected.clear();
    Inlet inlet;
    Outlet outlet;
    inlet >> *this >> outlet;
    float out = outlet.run(t, x);
    connected = wasConnected;
    return out;
}

float Node::first(float t, float x)
{
    if (connected.size() == 0) {
        throw "Node did not have any connections";
    }
    
    Node *node = connected.front();
    
    if (node->visited) {
        return node->lastOutput;
    }
    else {
        return node->process(t, x);
    }
}

float Node::sumConnections(float t, float x)
{
    float sum = 0;
    
    for (Node *node : connected) {
        if (node->visited) {
            sum += node->lastOutput;
        }
        else {
            sum += node->process(t, x);
        }
    }
    
    return sum;
}

bool Node::wasVisited()
{
    return visited;
}

void Node::begin()
{
    visited = true;
}

float Node::finish(float output)
{
    lastOutput = output;
    return output;
}

void Node::operator>>= (Node &other)
{
    connect(other);
}


Node &Node::operator>>(Node &other)
{
    other.connected.push_back(this);
    return other;
}

Node &Node::operator>>(Chain &chain)
{
    *this >>= *chain.first;
    return *chain.last;
}

Chain Node::operator>(Node &other)
{
    Chain chain;
    *this >>= other;
    chain.first = this;
    chain.last = &other;
    return chain;
}

Chain Node::operator>(Chain &chain)
{
    *this >>= *chain.first;
    Chain newChain;
    newChain.first = this;
    newChain.last = chain.last;
    return newChain;
}
