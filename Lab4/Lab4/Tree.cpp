#include "Tree.h"
#include "Branch.h"

Tree::Tree(int depth)
{
    _depth = depth;
    _root = new Branch(0, _depth);
}

Node* Tree::GetRoot()
{
    return _root;
}

int Tree::GetTreeDepth()
{
    return _depth;
}

Tree::~Tree()
{
    delete _root;
}
