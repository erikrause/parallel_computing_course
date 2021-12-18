#include "Branch.h"
#include "Leaf.h"
#include <cstdlib>

Branch::Branch(int layer, int maxLayers)
{
    _layer = layer;

    if (_layer < maxLayers)
    {
        _children1 = new Branch(layer + 1, maxLayers);
        _children2 = new Branch(layer + 1, maxLayers);
    }
    else
    {
        _children1 = new Leaf(rand() % 100);
        _children2 = new Leaf(rand() % 100);
    }
}

Node* Branch::GetChildren1()
{
    return _children1;
}

Node* Branch::GetChildren2()
{
    return _children1;
}

int Branch::GetSumChildrensValues()
{
    int children1Values = _children1->GetSumChildrensValues();
    int children2Values = _children2->GetSumChildrensValues();

    return children1Values + children2Values;
}

void Branch::AddValueEachChildren(int value)
{
#pragma omp task
    {
        _children1->AddValueEachChildren(value);
        _children2->AddValueEachChildren(value);
    }
#pragma omp taskwait
}

Branch::~Branch()
{
    delete _children1;
    delete _children2;
}
