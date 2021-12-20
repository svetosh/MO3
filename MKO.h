#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

class MKO
{
private:
	int** mtrx;									// �������
	int m = 4;									// ���������� �����������
	int n = 4;									// ���������� ���������
	std::vector <std::string> line_criteria;    // ��������
	std::vector <std::string> alternatives;		// ������������
public:
	MKO();
	~MKO();
	void print();
	void restrictions();
	void pareto();
	void weighing_and_combining();
	void hierarchies();
};