#pragma once
#include <vector>

class Vector 
{
public:
	std::vector<double> input_vector;

	// Constructor
	Vector(std::vector<double> input_vector);

	double length() const;
	bool is_zero(const double& tolerance) const;
	Vector normalise();
	double dot_product(Vector vec) ;
	int size() const;
	Vector cross_product(Vector vec) const;
	double distance(Vector vec) const;

	double operator[](int i) const;
	bool operator==(const Vector& vec2);
	Vector operator+(Vector& vec2) const;
	Vector operator-(Vector& vec2) const;
	Vector operator*(Vector& vec2) const;
	Vector operator*(const double& number) const;
	Vector operator+(const double& number) const;
	Vector operator-() const;
};

Vector operator*(const double& number, Vector vec);
Vector operator+(const double& number, Vector vec);
