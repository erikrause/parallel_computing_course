#pragma once
#include "Node.h"

class Leaf : public Node
{
public:
	
	Leaf(int value);

	int GetValue();

	int GetSumChildrensValues();
	void AddValueEachChildren(int value);

protected:
	int _value;
};

