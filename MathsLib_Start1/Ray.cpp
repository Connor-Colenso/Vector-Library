#include <cmath>
#include <vector>
#include <stdexcept>
#include "Ray.h"
#include "Vector.h"

// Constructor for the Ray class.
Ray::Ray(Vector position, Vector direction) : position{ position }, direction{ direction }
{

    if ((position.size() != 3) && (direction.size() != 3))
    {
        throw std::invalid_argument("Position and direction vectors are not three dimensional.");
    }

}

// Operator overloading.
Ray Ray::operator-()
{
    Ray ray(-position, -direction);
    return ray;
}

Ray Ray::operator-(Ray ray)
{
    Ray ray_new(position - ray.position, direction - ray.direction);
    return ray_new;
}

Ray Ray::operator+(Ray ray)
{
    Ray ray_new(position + ray.position, direction + ray.direction);
    return ray_new;
}

Ray Ray::operator*(double number)
{
    Ray ray_new(position * number, direction * number);
    return ray_new;
}

// Methods on ray.
double Ray::point_distance(Vector M0)
{
    Vector tmp_1 = (M0 - position);
    Vector tmp_2 = tmp_1.cross_product(direction);

    return tmp_2.length() / direction.length();
}

double Ray::line_distance(Ray ray)
{

    Vector n = (direction).cross_product(ray.direction);

    if (n.is_zero(10e-6))
    {
        double d = ((direction).cross_product(ray.position - position)).length() / (direction).length();

        return abs(d);
    }

    double d = n.dot_product(ray.position - position) / n.length();

    return abs(d);

}

bool Ray::intersect(Ray ray)
{

    if ((((direction).cross_product(ray.direction)).dot_product(ray.position - position)) == 0)
    {
        return true;
    }

    return false;
}
