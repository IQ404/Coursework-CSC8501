
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <iostream>

template <typename T>
class Matrix {
public:
	Matrix(int m = default_row, int n = default_column);
	~Matrix();

	int get_row_size() const { return row_size; };
	int get_column_size() const { return column_size; };
	T get_element(int x, int y) const;
	void set_element(int x, int y, T elem);

	void print_matrix();  // To std::cout

	void row_reduction();

	//void integral_normalization();

protected:
	struct Position
	{
		int row = -1;
		int column = -1;
		void set(int m, int n) {
			row = m;
			column = n;
		}
		bool valid() {
			if (row == -1 || column == -1) return false;
			return true;
		}
	};
	static const int default_row = 5;
	static const int default_column = 6;
	T** cells = nullptr;
	int row_size = 0;
	int column_size = 0;

	void add_row_to_row(const T& a, int row_i, int row_j);
	void interchange_rows(int row_i, int row_j);
	void multiply_row(const T& c, int row);

	void clear_column(const Position& p);
	Position find_pivot(int row_i);
	void reduce_row(int row_i, bool& finish);
	//void use_bounds(int i, int j);
};

#include "MatrixDefinition.h"

#endif // !MATRIX_H_INCLUDED
