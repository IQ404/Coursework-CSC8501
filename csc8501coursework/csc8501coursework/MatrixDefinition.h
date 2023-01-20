
#ifndef MATRIXDEFINITION_H_INCLUDED
#define MATRIXDEFINITION_H_INCLUDED

#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix(int m, int n)
	: row_size{ m }, column_size{ n }
{
	cells = new T * [row_size];
	for (int i = 0; i < row_size; i++) {
		cells[i] = new T[column_size];
		std::memset(cells[i], 0, column_size * sizeof(T));
	}
}

template <typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < row_size; i++) {
		delete[] cells[i];
	}
	delete[] cells;
}

template <typename T>
T Matrix<T>::get_element(int x, int y) const
{
	return cells[x][y];
}

template <typename T>
void Matrix<T>::set_element(int x, int y, T elem)
{
	cells[x][y] = elem;
}

template <typename T>
void Matrix<T>::print_matrix()
{
	for (int i = 0; i < row_size; i++) {
		for (int j = 0; j < column_size; j++) {
			std::cout << cells[i][j] << '\t';
		}
		std::cout << '\n';
	}
}

template <typename T>
void Matrix<T>::add_row_to_row(const T& a, int row_i, int row_j)
{
	T* row_multiple = new T[column_size];
	for (int i = 0; i < column_size; i++) {
		row_multiple[i] = cells[row_i - 1][i] * a;
		cells[row_j - 1][i] = row_multiple[i] + cells[row_j - 1][i];
	}
	delete[] row_multiple;
}

template <typename T>
void Matrix<T>::interchange_rows(int row_i, int row_j)
{
	T* row_i_copy = new T[column_size];
	std::memcpy(row_i_copy, cells[row_i - 1], column_size * sizeof(T));
	delete[] cells[row_i - 1];
	cells[row_i - 1] = cells[row_j - 1];
	cells[row_j - 1] = row_i_copy;
}

template <typename T>
void Matrix<T>::multiply_row(const T& c, int row)
{
	for (int i = 0; i < column_size; i++) {
		cells[row - 1][i] = cells[row - 1][i] * c;
	}
}

template <typename T>
void Matrix<T>::row_reduction()
{
	bool finish = false;
	for (int i = 0; i < row_size; i++) {
		reduce_row(i + 1, finish);
		if (finish) break;
	}
}

template <typename T>
void Matrix<T>::reduce_row(int row_i, bool& finish)
{
	Position p = find_pivot(row_i);
	if (!p.valid()) {
		finish = true;
		return;
	}
	interchange_rows(row_i, p.row + 1);
	p.row = row_i - 1;
	multiply_row(1 / (cells[p.row][p.column]), p.row + 1);
	clear_column(p);
}

template <typename T>
typename Matrix<T>::Position Matrix<T>::find_pivot(int row_i)
{
	for (int column = 0; column < column_size - 1; column++) {
		for (int row = row_i - 1; row < row_size; row++) {
			if (cells[row][column] != 0) {
				return Position{ row, column };
			}
		}
	}
	return Position{};
}

template <typename T>
void Matrix<T>::clear_column(const Position& p)
{
	for (int i = p.row + 1; i < row_size; i++) {
		if (cells[i][p.column] == 0) continue;
		add_row_to_row((cells[i][p.column]) * (-1), p.row + 1, i + 1);
	}
	for (int i = p.row - 1; i >= 0; i--) {
		if (cells[i][p.column] == 0) continue;
		add_row_to_row((cells[i][p.column]) * (-1), p.row + 1, i + 1);
	}
}

//template <typename T>
//void Matrix<T>::use_bounds(int i, int j)
//{
//	int upper_bound = ((cells[i][j] + 1) > 0) ? int(cells[i][j] + 1) : (int(cells[i][j] + 1) - 1);
//	int lower_bound = ((cells[i][j] - 1) < 0) ? int(cells[i][j] - 1) : (int(cells[i][j] - 1) + 1);
//	if (upper_bound - cells[i][j] < cells[i][j] - lower_bound) cells[i][j] = upper_bound;
//	else cells[i][j] = lower_bound;
//}
//
//template <typename T>
//void Matrix<T>::integral_normalization()
//{
//	for (int i = 0; i < row_size; i++) {
//		for (int j = 0; j < column_size; j++) {
//			if (cells[i][j] == int(cells[i][j])) {
//				cells[i][j] = int(cells[i][j]);
//				continue;
//			}
//			use_bounds(i, j);
//		}
//	}
//}

#endif // !MATRIXDEFINITION_H_INCLUDED
