#pragma once
#include "Vector.h"


class Matrix
{

public:
    std::vector<Vector> matrix;
    Matrix(std::vector<Vector> matrix);
    const Vector operator[](const int index);
    int height;
    int length;
};

Vector operator*(Matrix matrix, Vector vector);