#pragma once

class Node
{
public:

	/// <summary>
	/// ���������� ����� values ���� �������� ����������.
	/// </summary>
	/// <returns> ����� values ���� �������� </returns>
	virtual int GetSumChildrensValues() = 0;

	/// <summary>
	/// ��������� (+) �������� � ������� ������� ����������.
	/// </summary>
	/// <param name="value"> �������� ��� ������������. </param>
	virtual void AddValueEachChildren(int value) = 0;

	virtual ~Node();
};
