#include "Matrix.h"
#include <cassert>

int main()
{
	size_t rows = 3;
	size_t cols = 5;

	Matrix m1(rows, cols);
	Matrix m2(rows, cols);
	Matrix m3(rows, cols);

	// You can check matrix sizes
	assert(m1.get_columns() == cols);
	assert(m1.get_rows() == rows);

	// All matrices are initialized with zeros
	// Matrices can be compared
	assert(m1 == m2);
	assert(m2 == m3);
	assert(m1 == m3);
	assert(m1[0][0] == 0);

	// Elements can be modified
	m1[1][1] = 3;
	m2[1][1] = 5;
	m3[1][1] = 8;

	assert(m1[1][1] == 3);
	assert(m2[1][1] == 5);
	assert(m3[1][1] == 8);

	// Matrices can be checked on inequality
	assert(m1 != m2);
	assert(m2 != m3);
	assert(m1 != m3);

	// Matrices can be added
	Matrix m4 = m1 + m2;

	assert(m4 == m3);
	assert(m4 != m1);

	// Matrix can be multiplied by int
	m3[1][1] = 21;
	m1 *= 7;

	assert(m1 == m3);

	Matrix m5(cols, rows);
	
	// Matrices with conflicting sizes cannot be added
	try
	{
		m1 = m2 + m5;
	}
	catch (std::out_of_range ex)
	{
		std::cout << ex.what() << std::endl;
	}

	// Element with invalid index cannot be extracted
	try
	{
		int elem = m1[100][100];
	}
	catch (std::out_of_range ex)
	{
		std::cout << ex.what() << std::endl;
	}

	Matrix M(rows, cols);

	int n = M.get_rows();
	int m = M.get_columns();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i][j] = i * j;

	// Matrix can be printed
	std::cout << M << std::endl;

	return 0;
}