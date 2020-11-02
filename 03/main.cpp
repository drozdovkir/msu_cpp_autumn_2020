#include "Matrix.h"

int main()
{
	int rows = 0;
	int cols = 0;

	std::cout << "Enter size of matrix:" << std::endl;
	std::cout << "Rows = ";
	std::cin >> rows;

	std::cout << "Columns = ";
	std::cin >> cols;

	Matrix m(rows, cols);

	std::cout << "Now enter elements of your matrix:" << std::endl;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			std::cin >> m[i][j];

	int k = 0;

	std::cout << "Enter a number:" << std::endl;
	std::cout << "k = ";
	std::cin >> k;

	m *= k;

	std::cout << "Here is your matrix multiplied by k. Enjoy!" << std::endl;
	std::cout << m;

	return 0;
}