#pragma once

//------------------------------------------------------------------------------
// include files
#include <cmath>
#include <vector>
#include <stdexcept>

// Definition of our vector class:

// This is essentially a wrapper around std::vector that allows us to perform additional 
// calculations as if it was a mathematical vector.

#include "Vector.h"

// Constructor for the Vector class.
Vector::Vector(std::vector<double> input_vector) : input_vector( input_vector ) { };

// Calculates the Euclidean distance of the vector from the origin.
double Vector::length() const
{
	// Dummy variable used for counting.
	double tmp_sum = 0;

	// Iterate over each value in the vector and sum the squared values.
	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_sum += pow(input_vector[i], 2);
	}
	return sqrt(tmp_sum);
}

// Checks if the vector is approximately equal to the zero vector, useful helper function. Returns either true or false.
bool Vector::is_zero(const double& tolerance) const
{
	for (int i = 0; i < input_vector.size(); i++)
	{
		// If any value but 0 is found then it returns false.
		if (abs(input_vector[i]) > tolerance) {
			return false;
		};
	}
	return true;
}

// Returns a normalised vector object, that 
Vector Vector::normalise()
{
	// Derefence the this pointer and use the fact that we have operator 
	// overloaded Vector * double to greatly simplify this code.
	double vector_length = this->length();
	return (*this) * (1 / vector_length);
}

// Calculate dot product between two vectors.
double Vector::dot_product(Vector vec)
{
	// Check that the sizes of the vectors are equal.
	if (this->size() != vec.size())
	{
		throw std::invalid_argument("Vectors used for dot product are not the same size.");
	}

	std::vector<double> tmp_array;
	double tmp_sum = 0;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_sum += input_vector[i] * vec.input_vector[i];
	}
	return tmp_sum;
}

// Returns the dimensionality of the vector.
int Vector::size() const
{
	return (int) input_vector.size();
}

// Calculate a cross product, only works with 3D vectors.
Vector Vector::cross_product(Vector vec) const
{

	if ((input_vector.size() != 3) || (vec.size() != 3))
	{
		throw std::invalid_argument("Vectors have invalid dimensions. Only three dimensional vectors can utilise the cross product operator.");
	}

	std::vector<double> tmp_array = {};

	tmp_array.push_back((input_vector[1] * vec[2] - input_vector[2] * vec[1]));
	tmp_array.push_back((input_vector[2] * vec[0] - input_vector[0] * vec[2]));
	tmp_array.push_back((input_vector[0] * vec[1] - input_vector[1] * vec[0]));

	Vector new_vec(tmp_array);

	return new_vec;

}

double Vector::distance(Vector vec) const
{
	if (vec.size() != this->size())
	{
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	double tmp_sum = 0;

	for (int i = 0; i < vec.size(); i++)
	{
		tmp_sum += pow(this->input_vector[i] - vec[i], 2);
	}

	return sqrt(tmp_sum);
}

double Vector::operator[](int i) const
{
	return input_vector[i];
}


Vector Vector::operator+(Vector& vec2) const
{
	if (vec2.size() != this->size())
	{
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	std::vector<double> tmp_array;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_array.push_back(input_vector[i] + vec2[i]);
	}

	return Vector(tmp_array);
}

bool Vector::operator==(const Vector& vec2)
{
	if (vec2.size() != input_vector.size())
	{
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	for (int i = 0; i < input_vector.size(); i++)
	{
		if (input_vector[i] != vec2[i]) 
		{ 
			return false; 
		}
	}

	return true;
}



Vector Vector::operator-(Vector& vec2) const
{
	if (vec2.size() != this->size())
	{
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	std::vector<double> tmp_array;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_array.push_back(input_vector[i] - vec2[i]);
	}

	return Vector(tmp_array);
}

Vector Vector::operator*(Vector& vec2) const
{
	if (vec2.size() != this->size())
	{
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	std::vector<double> tmp_array;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_array.push_back(input_vector[i] * vec2[i]);
	}

	return Vector(tmp_array);
}


Vector Vector::operator*(const double& number) const
{
	std::vector<double> tmp_array;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_array.push_back(number * input_vector[i]);
	}

	return Vector(tmp_array);
}

Vector Vector::operator+(const double& number) const
{
	std::vector<double> tmp_array;

	for (int i = 0; i < input_vector.size(); i++)
	{
		tmp_array.push_back(number + input_vector[i]);
	}

	return Vector(tmp_array);
}

Vector Vector::operator-() const
{
	Vector vec(input_vector);
	return vec * -1;
}

// Helper functions
Vector operator*(const double& number, Vector vec)
{
	return vec * number;
}

Vector operator+(const double& number, Vector vec)
{
	return vec + number;
}