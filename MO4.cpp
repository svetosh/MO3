#include <iostream>
#include "MKO.h"

int main()
{
	setlocale(LC_ALL, "RUS");
	MKO test_5;
	test_5.print();
	test_5.restrictions();
	test_5.pareto();
	test_5.weighing_and_combining();
	test_5.hierarchies();
}