#pragma once

class Node
{
public:

	/// <summary>
	/// Возвращает сумму values всех потомков рекурсивно.
	/// </summary>
	/// <returns> Сумма values всех потомков </returns>
	virtual int GetSumChildrensValues() = 0;

	/// <summary>
	/// Добавляет (+) значение к каждому потомку рекурсивно.
	/// </summary>
	/// <param name="value"> Значение для суммирования. </param>
	virtual void AddValueEachChildren(int value) = 0;

	virtual ~Node();
};
