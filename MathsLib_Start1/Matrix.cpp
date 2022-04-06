#include "Matrix.h"
#include <vector>
#include <stdexcept>

// Matrix Constructor.
Matrix::Matrix(std::vector<Vector> matrix) : matrix{ matrix }
{
	height = matrix[0].size();
	length = (int) matrix.size();
}

const Vector Matrix::operator[](const int index)
{
	return matrix[index];
}

// This is actually really simple to add Matrix * Vector for but time is too limited.
Vector operator*(Matrix matrix, Vector vector)
{
	if (matrix.height == vector.size())
	{
		throw std::invalid_argument("Matrix vector product has invalid dimensions.");
	}

	std::vector<double> tmp_vec;

	for (int i = 0; i < matrix.height; i++) 
	{
		tmp_vec.push_back(vector.dot_product(matrix[i]));
	}

	return Vector(tmp_vec);
}