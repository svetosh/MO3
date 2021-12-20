#include "MKO.h"

MKO::MKO()
{
	alternatives.push_back("Suzuki");
	alternatives.push_back("Mitsub");
	alternatives.push_back("Honda");
	alternatives.push_back("Toyota");
	line_criteria.push_back("COST");
	line_criteria.push_back("SERVIC");
	line_criteria.push_back("GAS");
	line_criteria.push_back("COMF");
	mtrx = new int* [m];
	for (int i = 0; i < m; i++)
	{
		mtrx[i] = new int[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << "Введите оценку " << alternatives[i] << " по критерию " << line_criteria[j] << " используя 1 4 8 10, где 1 самый низкий:";
			std::cin >> mtrx[i][j];
		}
	}
	std::cout << std::endl;
}

MKO::~MKO()
{
	for (int i = 0; i < m; i++)
	{
		delete[] mtrx[i];
	}
}

void MKO::print()
{
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line_criteria[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i];
		for (int j = 0; j < n; j++)
		{
			std::cout << "\t|" << mtrx[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void MKO::restrictions()
{
	std::vector <double> criteria;
	std::cout << "Метод замены критериев ограничениями." << std::endl << "Выберите главный критерий:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << " " << line_criteria[i] << std::endl;
	}
	std::cout << std::endl;
	int choice = 0;
	std::cout << "Ваш выбор: ";
	std::cin >> choice;
	choice -= 1;
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		if (i != choice)
		{
			std::cout << "Введите допустимый уровень для критерия " << line_criteria[i] << " от 0.0 до 0.9: ";
			double tmp;
			std::cin >> tmp;
			criteria.push_back(tmp);
		}
		else
		{
			criteria.push_back(1);
		}
	}
	std::cout << std::endl;
	double** new_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		new_mtrx[i] = new double[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j != choice)
			{
				if (j == 0)
				{
					new_mtrx[i][j] = std::abs(((double)mtrx[i][j] - 10) / -10);
				}
				else
				{
					new_mtrx[i][j] = (double)mtrx[i][j] / 10;
				}
			}
			else
			{
				new_mtrx[i][j] = mtrx[i][j];
			}
		}
	}

	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line_criteria[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i];
		for (int j = 0; j < n; j++)
		{
			std::cout << "\t|" << std::setprecision(3) << new_mtrx[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector <int> positions;
	for (int i = 0; i < m; i++)
	{
		if (positions.empty())
		{
			positions.push_back(i);
		}
		else if (new_mtrx[i][choice] < new_mtrx[positions[0]][choice])
		{
			positions.insert(positions.begin(), i);
		}
		else if (new_mtrx[i][choice] > new_mtrx[positions[positions.size() - 1]][choice])
		{
			positions.push_back(i);
		}
		else
		{
			int pos = 1;
			while (new_mtrx[i][choice] > new_mtrx[positions[pos]][choice])
			{
				pos += 1;
			}
			positions.insert(positions.begin() + pos, i);
		}
	}
	for (int i = m - 1; i >= 0; i--)
	{
		bool check = false;
		for (int j = 0; j < n; j++)
		{
			if (j != choice)
			{
				if (new_mtrx[positions[i]][j] < criteria[j])
				{
					check = true;
				}
			}
		}
		if (check == false)
		{
			std::cout << "Ответ: " << alternatives[positions[i]] << std::endl;
			return;
		}
	}
}

void MKO::pareto()
{
	std::cout << "Метод формирования и сужения множества Парето." << std::endl 
			  << "Выберите главный критерий 1:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << " " << line_criteria[i] << std::endl;;
	}
	std::cout << std::endl;
	int choice_1 = 0;
	std::cout << "Ваш выбор: ";
	std::cin >> choice_1;
	std::cout << std::endl << "Выберите главный критерий 2:" << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << " " << line_criteria[i] << std::endl;
	}
	std::cout << std::endl;
	int choice_2 = 0;
	std::cout << "Ваш выбор: ";
	std::cin >> choice_2;
	choice_1 -= 1;
	choice_2 -= 1;
	std::cout << std::endl;
	double min_length = 10 * sqrt(2);
	int pos = 0;
	int optimum = -1;
	if (choice_1 == 0)
	{
		std::cout << "Точка утопии: (0, 10)" << std::endl;
		optimum = 0;
	}
	else if (choice_2 == 0)
	{
		std::cout << "Точка утопии: (10, 0)" << std::endl;
		optimum = 1;
	}
	else
	{
		std::cout << "Точка утопии: (10, 10)" << std::endl;
	}
	std::cout << std::endl << "Координаты точек:" << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i] << " - (" << mtrx[i][choice_1] << ", " << mtrx[i][choice_2] << ")" << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		if (optimum == -1)
		{
			if (sqrt((double)pow((10 - mtrx[i][choice_1]), 2) + (double)pow((10 - mtrx[i][choice_2]), 2)) < min_length)
			{
				min_length = sqrt((10 - mtrx[i][choice_1]) ^ 2 + (10 - mtrx[i][choice_2]) ^ 2);
				pos = i;
			}
		}
		else if (optimum == 0)
		{
			if (sqrt((double)pow((0 - mtrx[i][choice_1]), 2) + (double)pow((10 - mtrx[i][choice_2]), 2)) < min_length)
			{
				min_length = sqrt((10 - mtrx[i][choice_1]) ^ 2 + (10 - mtrx[i][choice_2]) ^ 2);
				pos = i;
			}
		}
		else
		{
			if (sqrt((double)pow((10 - mtrx[i][choice_1]), 2) + (double)pow((0 - mtrx[i][choice_2]), 2)) < min_length)
			{
				min_length = sqrt((10 - mtrx[i][choice_1]) ^ 2 + (10 - mtrx[i][choice_2]) ^ 2);
				pos = i;
			}
		}
	}
	std::cout << "Ответ: " << alternatives[pos] << std::endl << std::endl;
}

void MKO::weighing_and_combining()
{
	std::cout << "Метод взвешивания и объединения критериев." << std::endl << std::endl;
	//Составим матрицу рейтингов альтернатив по критериям, используя шкалу 1:10, и изменим её так, чтобы каждый критерий надо было максимизировать
	line_criteria[0] = "LOWCOS";
	int** new_mtrx = new int* [m];
	for (int i = 0; i < m; i++)
	{
		new_mtrx[i] = new int[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (j == 0)
			{
				new_mtrx[i][j] = abs(10 - mtrx[i][j]);
			}
			else
			{
				new_mtrx[i][j] = mtrx[i][j];
			}
		}
	}
	std::cout << std::endl;

	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line_criteria[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i];
		for (int j = 0; j < n; j++)
		{
			std::cout << "\t|" << std::setprecision(3) << new_mtrx[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Нормализуем её:" << std::endl;
	std::vector <int> sums;
	for (int i = 0; i < n; i++)
	{
		int tmp = 0;
		for (int j = 0; j < m; j++)
		{
			tmp += new_mtrx[j][i];
		}
		sums.push_back(tmp);
	}
	double** norm_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		norm_mtrx[i] = new double[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::string tmp = std::to_string((double)(new_mtrx[j][i]) / sums[i]);
			std::string double_str = tmp.substr(0, 4);
			norm_mtrx[j][i] = std::stod(double_str);
		}
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line_criteria[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i];
		for (int j = 0; j < n; j++)
		{
			std::cout << "\t|" << std::setprecision(3) << norm_mtrx[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < m; i++)
	{
		delete[] new_mtrx[i];
	}

	double** krit_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		krit_mtrx[i] = new double[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			krit_mtrx[i][j] = -1;
		}
	}
	std::cout << "Введите экспертную оценку критериев:" << std::endl
		<< "Если критерий 1 важнее критерия 2 введите <1>" << std::endl
		<< "Если критерий 2 важнее критерия 1 введите <0>" << std::endl
		<< "Если критерии равнозначны введите <0.5>" << std::endl << std::endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				if (krit_mtrx[j][i] == -1)
				{
					double choice;
					std::cout << "Критерий  " << line_criteria[i] << " критерия  " << line_criteria[j] << "  ";
					std::cin >> choice;
					krit_mtrx[i][j] = choice;
				}
				else
				{
					krit_mtrx[i][j] = abs(krit_mtrx[j][i] - 1);
				}
			}
		}
	}
	std::cout << std::endl;
	std::vector <double> alpha;
	for (int i = 0; i < m; i++)
	{
		double sum_tmp = 0;
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				sum_tmp += krit_mtrx[i][j];
			}
		}
		alpha.push_back(sum_tmp);
	}
	for (int i = 0; i < m; i++)
	{
		delete[] krit_mtrx[i];
	}
	std::vector <double> norm_alpha;
	double sum_rez = 0;
	for (double& h : alpha)
	{
		sum_rez += h;
	}
	for (double& h : alpha)
	{
		std::string tmp_str = std::to_string(h / sum_rez);
		std::string double_str = tmp_str.substr(0, 4);
		norm_alpha.push_back(std::stod(double_str));
	}
	std::cout << std::endl << "Нормализованный вектор весов критериев: ( ";
	for (double& h : norm_alpha)
	{
		std::cout << h << " ";
	}
	std::cout << ')' << std::endl;

	std::vector <double> rez;
	for (int i = 0; i < m; i++) // Умножить нормализованную матрицу на нормализованный вектор весов критериев
	{
		double _rez = 0;
		for (int j = 0; j < n; j++)
		{
			_rez += norm_mtrx[i][j] * norm_alpha[j];
		}
		std::string tmp_str = std::to_string(_rez);
		std::string double_str = tmp_str.substr(0, 4);
		rez.push_back(_rez);
	}
	std::cout << "Значения объединенного критерия для всех альтернатив: (";
	for (double& h : rez)
	{
		std::cout << h << " ";
	}
	std::cout << ")" << std::endl;
	double max_rez = 0;
	int _pos = 0;
	for (int i = 0; i < rez.size(); i++)
	{
		if (rez[i] > max_rez)
		{
			max_rez = rez[i];
			_pos = i;
		}
	}
	std::cout << "Ответ: " << alternatives[_pos] << std::endl << std::endl;
	for (int i = 0; i < m; i++)
	{
		delete[] norm_mtrx[i];
	}
}

double Comparison(int& lhs, int& rhs)
{
	if (lhs - rhs == 0)
	{
		return 1;
	}
	else if (lhs - rhs < 5)
	{
		return 3;
	}
	else if ((lhs - rhs >= 5) && (lhs - rhs < 8))
	{
		return 5;
	}
	else
	{
		return 7;
	}
}

int Criteria_weight(int& rhs)
{
	if (rhs == 0)
	{
		return 10;
	}
	else if (rhs == 1)
	{
		return 8;
	}
	else if (rhs == 2)
	{
		return 4;
	}
	else
	{
		return 1;
	}
}

void MKO::hierarchies()
{
	std::cout << "Метод анализа иерархий." << std::endl;
	line_criteria[0] = "LOWCOS";
	for (int i = 0; i < m; i++) //из критериев составим и нормализуем матрицу попарного сравнения альтернатив
	{
		mtrx[i][0] = abs(10 - mtrx[i][0]);
	}
	std::vector <std::string> alternatives_tmp;
	for (std::string& h : line_criteria)
	{
		alternatives_tmp.push_back(h);
	}
	double** norm_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		norm_mtrx[i] = new double[n];
	}
	double** new_mtrx = new double* [m];
	for (int i = 0; i < m; i++)
	{
		new_mtrx[i] = new double[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			new_mtrx[i][j] = -1;
		}
	}
	for (int h = 0; h < n; h++)
	{
		std::cout << line_criteria[h] << std::endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == j)
				{
					new_mtrx[i][j] = 1;
				}
				else if (new_mtrx[j][i] == -1)
				{
					if (mtrx[i][h] >= mtrx[j][h])
					{
						new_mtrx[i][j] = Comparison(mtrx[i][h], mtrx[j][h]);
						new_mtrx[j][i] = 1 / Comparison(mtrx[i][h], mtrx[j][h]);
						std::string tmp = std::to_string(new_mtrx[j][i]);
						std::string double_tmp = tmp.substr(0, 4);
						new_mtrx[j][i] = std::stod(double_tmp);
					}
					else
					{
						new_mtrx[i][j] = 1 / Comparison(mtrx[j][h], mtrx[i][h]);
						std::string tmp = std::to_string(new_mtrx[i][j]);
						std::string double_tmp = tmp.substr(0, 4);
						new_mtrx[i][j] = std::stod(double_tmp);
						new_mtrx[j][i] = Comparison(mtrx[j][h], mtrx[i][h]);
					}
				}
			}
		}

		std::cout << std::endl;
		for (int i = 0; i < n; i++)
		{
			std::cout << "\t|" << line_criteria[i];
		}
		std::cout << std::endl;
		for (int i = 0; i < m; i++)
		{
			std::cout << alternatives[i];
			for (int j = 0; j < n; j++)
			{
				std::cout << "\t|" << std::setprecision(4) << new_mtrx[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		std::vector <double> norm_vec;
		for (int i = 0; i < m; i++)
		{
			double tmp_sum = 0;
			for (int j = 0; j < n; j++)
			{
				tmp_sum += new_mtrx[i][j];
			}
			norm_vec.push_back(tmp_sum);
		}
		double sum = 0;
		for (double& x : norm_vec)
		{
			sum += x;
		}
		for (double& x : norm_vec)
		{
			double x_tmp = x / sum;
			std::string tmp = std::to_string(x_tmp);
			std::string double_tmp = tmp.substr(0, 4);
			x = std::stod(double_tmp);
		}
		std::cout << "Cумма по строке: ( ";
		for (double& x : norm_vec)
		{
			std::cout << x << " ";
		}
		std::cout << ")" << std::endl;
		for (int i = 0; i < m; i++)
		{
			norm_mtrx[i][h] = norm_vec[i];
		}
		std::vector <double> everage_geom;
		for (int i = 0; i < m; i++)
		{
			double ev = 1;
			for (int j = 0; j < n; j++)
			{
				ev *= new_mtrx[i][j];
			}
			ev = pow(ev, 0.25);
			everage_geom.push_back(ev);
		}
		double ev_sum = 0;
		for (double& x : everage_geom)
		{
			ev_sum += x;
		}
		for (double& x : everage_geom)
		{
			std::string ev_tmp = std::to_string(x / ev_sum);
			std::string ev_double = ev_tmp.substr(0, 4);
			x = std::stod(ev_double);
		}
		double lambda = 0;
		for (int i = 0; i < m; i++)
		{
			double lambda_sum = 0;
			for (int j = 0; j < n; j++)
			{
				lambda_sum += new_mtrx[j][i];
			}
			lambda_sum *= everage_geom[i];
			lambda += lambda_sum;
		}
		double IS;
		double PSS = 0.9;
		IS = abs((lambda - n) / (n - 1));
		std::string time = std::to_string(IS / PSS);
		std::string _time = time.substr(0, 4);
		double OS = std::stod(_time);
		std::cout << "Отношение согласованности = " << OS << std::endl;
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				new_mtrx[i][j] = -1;
			}
		}
	}
	int* weight = new int[n];
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << ". " << line_criteria[i] << " " << std::endl;
	}
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			std::cout << "Введите номер наиболее важного критерия: ";
		}
		else if (i == n - 1)
		{
			std::cout << "Введите номер наименее важного критерия: ";
		}
		else
		{
			std::cout << "Введите номер следующего по важности критерия: ";
		}
		int choice;
		std::cin >> choice;
		choice -= 1;
		weight[choice] = Criteria_weight(i);
	}
	for (int i = 0; i < m; i++)//Оценка приоритетов критериев
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				new_mtrx[i][j] = 1;
			}
			else if (new_mtrx[j][i] == -1)
			{
				if (weight[i] >= weight[j])
				{
					new_mtrx[i][j] = Comparison(weight[i], weight[j]);
					new_mtrx[j][i] = 1 / Comparison(weight[i], weight[j]);
					std::string tmp = std::to_string(new_mtrx[j][i]);
					std::string double_tmp = tmp.substr(0, 4);
					new_mtrx[j][i] = std::stod(double_tmp);
				}
				else
				{
					new_mtrx[i][j] = 1 / Comparison(weight[j], weight[i]);
					std::string tmp = std::to_string(new_mtrx[i][j]);
					std::string double_tmp = tmp.substr(0, 4);
					new_mtrx[i][j] = std::stod(double_tmp);
					new_mtrx[j][i] = Comparison(weight[j], weight[i]);
				}
			}
		}
	}

	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << "\t|" << line_criteria[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < m; i++)
	{
		std::cout << alternatives[i];
		for (int j = 0; j < n; j++)
		{
			std::cout << "\t|" << std::setprecision(4) << new_mtrx[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::vector <double> norm_vec_weight;
	for (int i = 0; i < m; i++)
	{
		double tmp_sum = 0;
		for (int j = 0; j < n; j++)
		{
			tmp_sum += new_mtrx[i][j];
		}
		norm_vec_weight.push_back(tmp_sum);
	}
	double sum = 0;
	for (double& x : norm_vec_weight)
	{
		sum += x;
	}
	for (double& x : norm_vec_weight)
	{
		double x_tmp = x / sum;
		std::string tmp = std::to_string(x_tmp);
		std::string double_tmp = tmp.substr(0, 4);
		x = std::stod(double_tmp);
	}
	std::cout << "Cумма по строке: ( " << std::endl;
	for (double& x : norm_vec_weight)
	{
		std::cout << x << " ";
	}
	std::cout << ")";
	std::vector <double> everage_geom;
	for (int i = 0; i < m; i++)
	{
		double ev = 1;
		for (int j = 0; j < n; j++)
		{
			ev *= new_mtrx[i][j];
		}
		ev = pow(ev, 0.25);
		everage_geom.push_back(ev);
	}
	double ev_sum = 0;
	for (double& x : everage_geom)
	{
		ev_sum += x;
	}
	for (double& x : everage_geom)
	{
		std::string ev_tmp = std::to_string(x / ev_sum);
		std::string ev_double = ev_tmp.substr(0, 4);
		x = std::stod(ev_double);
	}
	double lambda = 0;
	for (int i = 0; i < m; i++)
	{
		double lambda_sum = 0;
		for (int j = 0; j < n; j++)
		{
			lambda_sum += new_mtrx[j][i];
		}
		lambda_sum *= everage_geom[i];
		lambda += lambda_sum;
	}
	double IS;
	double PSS = 0.9;
	IS = abs((lambda - n) / (n - 1));
	std::string time = std::to_string(IS / PSS);
	std::string _time = time.substr(0, 4);
	double OS = std::stod(_time);
	std::cout << "Отношение согласованности = " << OS << std::endl;
	for (int i = 0; i < m; i++)
	{
		delete[] new_mtrx[i];
	}
	std::vector <double> rez;
	for (int i = 0; i < m; i++)//Составим матрицу и умножим на столбец оценки приоритетов
	{
		double _rez = 0;
		for (int j = 0; j < n; j++)
		{
			_rez += norm_mtrx[i][j] * norm_vec_weight[j];
		}
		std::string tmp_str = std::to_string(_rez);
		std::string double_str = tmp_str.substr(0, 4);
		rez.push_back(_rez);
	}
	std::cout << "Полученный вектор: ( ";
	for (double& h : rez)
	{
		std::cout << h << " ";
	}
	std::cout << ")" << std::endl;;
	double max_rez = 0;
	int _pos = 0;
	for (int i = 0; i < rez.size(); i++)
	{
		if (rez[i] > max_rez)
		{
			max_rez = rez[i];
			_pos = i;
		}
	}
	std::cout << "Ответ: " << alternatives[_pos] << std::endl;
	for (int i = 0; i < m; i++)
	{
		delete[] norm_mtrx[i];
	}
	delete[] weight;
}