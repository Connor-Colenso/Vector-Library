#pragma once
#include <stdexcept>
#include "Vector.h"


class Ray
{

public:
    Vector position, direction;
    Ray(Vector position, Vector direction);
    Ray operator-();
    Ray operator-(Ray ray);
    Ray operator+(Ray ray);
    Ray operator*(double number);

    double point_distance(Vector M0);
    double line_distance(Ray ray);
    bool intersect(Ray ray);
};