#include "Leaf.h"
#include <cmath>

Leaf::Leaf(int value)
{
	_value = value;
}

int Leaf::GetValue()
{
	return _value;
}

int Leaf::GetSumChildrensValues()
{
	return _value;
}

void Leaf::AddValueEachChildren(int value)
{
	_value += value;
}
