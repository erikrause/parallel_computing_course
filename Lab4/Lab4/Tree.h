#pragma once
#include "Node.h"

class Tree
{
public:

    Tree(int depth);

    Node* GetRoot();
    int GetTreeDepth();

    ~Tree();

protected:

    Node* _root;

    int _depth;
};

