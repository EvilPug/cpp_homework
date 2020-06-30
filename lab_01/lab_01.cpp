#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


template<typename T>
std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> matrix)
{
	std::vector<std::vector<T>> transposed(matrix[0].size(), std::vector<T>(matrix.size()));
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			transposed[j][i] = matrix[i][j];
		}

	}
	return transposed;
}


template<typename T>
std::vector<T> arange(T start, T stop, T step = 1) {
	std::vector<T> values;
	for (T value = start; value < stop; value += step)
		values.push_back(value);
	return values;
}

// Функции у
std::vector<double> generator(std::vector<double> x_list, int func_num) {

	std::vector<double> y_list;
	switch (func_num) {

	case 1:
		for (int i = 0; i < x_list.size(); i++)
		{
			y_list.push_back(-x_list[i]*log(x_list[i]));
		}
		return y_list;

	case 2:
		for (int i = 0; i < x_list.size(); i++)
		{
			y_list.push_back(sqrt(x_list[i]));
		}
		return y_list;

	case 3:
		for (int i = 0; i < x_list.size(); i++)
		{
			y_list.push_back(-pow(x_list[i], 2) - 0.5);
		}
		return y_list;

	case 4: 

		for (int i = 0; i < x_list.size(); i++)
		{
			y_list.push_back(sin(x_list[i]));
		}
		return y_list;

	default:
		std::cout << "Неверный номер функции!" << std::endl;
		std::cout << "Но мне нравится функция sqrt(x)" << std::endl;

		for (int i = 0; i < x_list.size(); i++)
		{
			y_list.push_back(sqrt(x_list[i]));
		}
		return y_list;
	}
}

template<typename T>
T find_min(std::vector<T> list) {

	T list_min = list[0];

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] < list_min) {
			list_min = list[i];
		}
	}

	return list_min;
}

template<typename T>
T find_max(std::vector<T> list) {

	T list_max = list[0];

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] > list_max) {
			list_max = list[i];
		}
	}

	return list_max;
}


int main()
{
	int func_num = 2;
	int width = 100;
	int height = 40;
	double x0;
	double x1;
	char empty_char = ' ';
	char filled_char = '#';
	char zero_char = '-';

	setlocale(LC_ALL, "Russian");

	std::cout << "1) -x * log(x) \n2) sqrt(x) \n3) -x^2 - 0.5 \n4) sin(x) \n" << std::endl;
	std::cout << "Введите номер функции: ";
	std::cin >> func_num;
	std::cout << "Введите параметры (длина высота x0 x1): ";
	std::cin >> width >> height >> x0 >> x1;


	
	
	double x_step = ((x1 - x0) / width);
	std::vector<double> x_list = arange(x0, x1, x_step);


	std::vector<double> y_list = generator(x_list, func_num);
	double y_min = find_min(y_list);
	double y_max = find_max(y_list);
	double y_step;

	if (func_num == 4) {
		y_step = (y_max - y_min) / height;
	}
	else {
		y_step = (y_max - y_min) / height + 0.02;
	}
	

	std::vector<int> x_transformed;
	for (int i = 0; i < x_list.size(); i++)
	{
		x_transformed.push_back(std::round(x_list[i] / x_step));
	}

	std::vector<int> y_transformed;
	for (int i = 0; i < y_list.size(); i++)
	{
		y_transformed.push_back(std::round(y_list[i] / -y_step));
	}



	// Обработка отрицательной части
	int min_remap_x = find_min(x_transformed);
	if (min_remap_x != 0) {
		for (int i = 0; i < x_transformed.size(); i++)
		{
			x_transformed[i] = x_transformed[i] - min_remap_x;
		}
	}

	int min_remap_y = find_min(y_transformed);
	if (min_remap_y < 0) {
		for (int i = 0; i < y_transformed.size(); i++)
		{
			y_transformed[i] = y_transformed[i] - min_remap_y;
		}
	}

	// Инициализируем пустую сетку
	std::vector<std::vector<char>> dot_list(height+20, std::vector<char>(width, empty_char));

	// Заполняем пересечения x и у
	for (int i = 0; i < width; i++)
	{
		dot_list[y_transformed[i]][x_transformed[i]] = filled_char;
	}


	// Вычиляем положение линии нуля
	if (y_min < 0 && y_max < 0) {

		for (int i = 0; i < width; i++)
		{
			dot_list[0][i] = zero_char;
		}

	} else if (y_min > 0 && y_max > 0) {

		for (int i = 0; i < width; i++)
		{
			dot_list[39][i] = zero_char;
		}

	}
	else if (y_max + y_min == 100){

		int zero_height = (find_max(y_transformed) - find_min(y_transformed))/2;

		for (int i = 0; i < width; i++)
		{
			dot_list[zero_height][i] = zero_char;
		}
	}

	else {

		int zero_height = height * abs(y_max) / (y_max - y_min);
		
		for (int i = 0; i < width; i++)
		{
			dot_list[zero_height][i] = zero_char;
		}

	}

	dot_list = transpose(dot_list);

	bool trigger_above;
	// Закрашиваем положительную по y часть графика
	for (int i = 0; i < dot_list.size(); i++)
	{
		trigger_above = false;

		for (int j = 0; j < dot_list[i].size(); j++)
		{
			if (dot_list[i][j] != empty_char) {
				trigger_above = true;
			}

			if (trigger_above == true && dot_list[i][j] != zero_char) {

				if (dot_list[i][j] != filled_char) {

					dot_list[i][j] = filled_char;

				}
				
			}
			else if (dot_list[i][j] == zero_char) {
				break;
			}
		}
	}

	bool trigger_below;
	// Закрашиваем отрицательную по y часть графика
	for (int i = dot_list.size()-1; i > 0; i--)
	{
		trigger_below = false;

		for (int j = dot_list[i].size()-1; j > 0; j--)
		{
			if (dot_list[i][j] != empty_char) {
				trigger_below = true;
			}

			if (trigger_below == true && dot_list[i][j] != zero_char) {

				if (dot_list[i][j] != filled_char) {

					dot_list[i][j] = filled_char;

				}

			}
			else if (dot_list[i][j] == zero_char) {
				break;
			}
		}
	}

	dot_list = transpose(dot_list);

	std::string outfile;
	outfile = "output" + std::to_string(func_num) + ".txt";
	std::ofstream Plot_File(outfile);

	// Рисуем график
	for (int i = 0; i < height; i++)
	{
		
		for (int j = 0; j < width; j++)
		{
			std::cout << dot_list[i][j];
			Plot_File << dot_list[i][j];
		}

		Plot_File << std::endl;
	}
	Plot_File.close();

	return 0;

}