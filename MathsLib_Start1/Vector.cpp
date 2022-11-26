#pragma once

// Definition of our vector class:

// This is essentially a wrapper around std::vector that allows us to perform additional 
// calculations as if it was a mathematical vector. Similar to valarray.

#include "Vector.h"

// Constructors for the Vector class.
Vector::Vector(std::vector<double> input_vector) : internal_vector{ input_vector } { };
Vector::Vector(std::initializer_list<double> input_vector) : internal_vector{ input_vector } { }
Vector::Vector(size_t n) : internal_vector(std::vector<double>(n, 0.0)) { }

// Calculates the Euclidean distance of the vector from the origin.
double Vector::euclidean_length() const {
	return sqrt((*this).dot_product(*this));
}

// Checks if the vector is approximately equal to the zero vector, useful helper function. Returns either true or false.
// Default value of 0 for tolerance if no value is provided.
bool Vector::is_zero(const double& tolerance) const noexcept {
	for (const auto& i : internal_vector) {
		// If any value but 0 is found then it returns false.
		if (abs(i) > tolerance) {
			return false;
		};
	}
	return true;
}

// Return normalised Vector object that has length of 1.
Vector Vector::normalise() {
	return Vector(internal_vector) / this->euclidean_length();
}

// Calculate dot product between two vectors.
double Vector::dot_product(const Vector& vec) const
{
	// Check that the sizes of the vectors are equal.
	if (this->size() != vec.size()) {
		throw std::invalid_argument("Vectors used for dot product are not the same size.");
	}

	return std::inner_product(vec.internal_vector.begin(), vec.internal_vector.end(), internal_vector.begin(), 0.0);
}

// Returns the dimensionality of the vector.
size_t Vector::size() const {
	return internal_vector.size();
}

// Calculate a cross product, only works with 3D vectors.
Vector Vector::cross_product(const Vector& vec) const {

	if ((internal_vector.size() != 3) || (vec.size() != 3)) {
		throw std::invalid_argument("Vectors have invalid dimensions. Only three dimensional vectors can utilise the cross product operator.");
	}

	std::vector<double> tmp_array;

	tmp_array.push_back((internal_vector[1] * vec[2] - internal_vector[2] * vec[1]));
	tmp_array.push_back((internal_vector[2] * vec[0] - internal_vector[0] * vec[2]));
	tmp_array.push_back((internal_vector[0] * vec[1] - internal_vector[1] * vec[0]));

	return Vector(tmp_array);

}

double Vector::distance(const Vector& vec) const {
	if (vec.size() != this->size()) {
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	const Vector tmp_vec = Vector(internal_vector) - vec;

	return tmp_vec.euclidean_length();
}

void Vector::print() const noexcept {

	for (const auto& i : internal_vector) {
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
}


std::vector<double> Vector::get_internal_storage() const noexcept {
	return internal_vector;
}

double Vector::operator[](const int& i) const {
	return internal_vector[i];
}


Vector Vector::operator+(const Vector& vec) const {
	if (vec.size() != this->size()) {
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	// Add the two vectors together and instantiate a new Vector object to return.
	std::vector<double> result = internal_vector;
	std::transform(result.begin(), result.end(), vec.internal_vector.begin(), result.begin(), std::plus<>());

	return Vector(result);
}

bool Vector::operator==(const Vector& vec) const {
	if (vec.size() != internal_vector.size()) {
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	return internal_vector == vec.internal_vector;
}

Vector Vector::operator-(const Vector& vec) const {
	if (vec.size() != this->size()) {
		throw std::invalid_argument("Vectors have invalid dimensions.");
	}

	// Subtract the two vectors together and instantiate a new Vector object to return.
	std::vector<double> result = internal_vector;
	std::transform(result.begin(), result.end(), vec.internal_vector.begin(), result.begin(), std::minus<>());

	return Vector(result);
}

Vector Vector::operator*(const double& number) const noexcept {

	std::vector<double> result = internal_vector;
	std::transform(result.begin(), result.end(), result.begin(), [number](const auto& i) { return number * i;  });

	return Vector(result);
}

Vector Vector::operator/(const double& number) const noexcept {
	return Vector(internal_vector) * (1.0 / number);
}

Vector Vector::operator-() const noexcept {
	return Vector(internal_vector) * -1;
}

// Friend method for operator overloading.
Vector operator*(const double& number, Vector vec) noexcept {
	return vec * number;
}
