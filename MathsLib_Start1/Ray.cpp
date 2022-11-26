#include <cmath>
#include <vector>
#include <stdexcept>
#include "Ray.h"
#include "Vector.h"

// Constructor for the Ray class.
Ray::Ray(Vector position, Vector direction) : position{ position }, direction{ direction } {
    if ((position.size() != 3) && (direction.size() != 3)) {
        throw std::invalid_argument("Position and direction vectors are not three dimensional.");
    }
}

// Operator overloading.
Ray Ray::operator-() {
    return Ray(-position, -direction);
}

Ray Ray::operator-(Ray ray) {
    return Ray(position - ray.position, direction - ray.direction);
}

Ray Ray::operator+(Ray ray) {
    return Ray(position + ray.position, direction + ray.direction);
}

Ray Ray::operator*(double number) {
    return Ray(position * number, direction * number);
}

// Methods on ray.
double Ray::point_distance(Vector M0) {
    Vector tmp_1 = (M0 - position);
    Vector tmp_2 = tmp_1.cross_product(direction);

    return tmp_2.euclidean_length() / direction.euclidean_length();
}

double Ray::line_distance(Ray ray) {

    Vector n = (direction).cross_product(ray.direction);

    if (n.is_zero(10e-6)) {
        double d = ((direction).cross_product(ray.position - position)).euclidean_length() / (direction).euclidean_length();
        return abs(d);
    }

    double d = n.dot_product(ray.position - position) / n.euclidean_length();
    return abs(d);

}

bool Ray::intersect(Ray ray) {
    if ((((direction).cross_product(ray.direction)).dot_product(ray.position - position)) == 0) {
        return true;
    }
    return false;
}
