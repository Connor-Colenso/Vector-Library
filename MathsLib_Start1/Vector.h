#pragma once
#include <vector>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <iostream>


class Vector {
	std::vector<double> internal_vector;
public:

	// Constructors.
	Vector(std::vector<double> input_vector);
	Vector(std::initializer_list<double> input_vector);
	explicit Vector(size_t n);

	double euclidean_length() const;
	bool is_zero(const double& tolerance = 0) const noexcept;
	Vector normalise();
	double dot_product(const Vector& vec) const;
	size_t size() const;
	Vector cross_product(const Vector& vec) const;
	double distance(const Vector& vec) const;
	void print() const noexcept;

	std::vector<double> get_internal_storage() const noexcept;

	// Iterators. Templates (auto) in header only.
	auto begin() const {
		return internal_vector.begin();
	}

	auto end() const {
		return internal_vector.end();
	}

	// Operator overloads.
	double operator[](const int& i) const;
	bool operator==(const Vector& _vec) const;
	Vector operator+(const Vector& _vec) const;
	Vector operator-(const Vector& _vec) const;
	Vector operator*(const double& number) const noexcept;
	Vector operator/(const double& number) const noexcept;
	Vector operator-() const noexcept;

	friend Vector operator*(const double& number, Vector _vec) noexcept;
};

