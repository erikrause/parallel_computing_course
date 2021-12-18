#pragma once
#include "Node.h"

class Branch : public Node
{
public:

    Branch(int layer, int maxLayers);

    Node* GetChildren1();
    Node* GetChildren2();

    int GetSumChildrensValues() override;
    void AddValueEachChildren(int value) override;

    ~Branch();

protected:

    Node* _children1;
    Node* _children2;

    int _layer;
};

