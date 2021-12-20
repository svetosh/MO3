#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

class MKO
{
private:
	int** mtrx;									// матрица
	int m = 4;									// количество альтернатив
	int n = 4;									// количество критериев
	std::vector <std::string> line_criteria;    // критерии
	std::vector <std::string> alternatives;		// альтернативы
public:
	MKO();
	~MKO();
	void print();
	void restrictions();
	void pareto();
	void weighing_and_combining();
	void hierarchies();
};