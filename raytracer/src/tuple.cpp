#include "tuple.hpp"
#include "point.hpp"
#include "vector.hpp"

std::ostream &operator<<(std::ostream &os, const raytracer::Tuple &tuple)
{
    os << "Tuple(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
    return os;
}

raytracer::Tuple operator*(double scalar, const raytracer::Tuple &tuple)
{
    return raytracer::Tuple(tuple.x * scalar, tuple.y * scalar, tuple.z * scalar, tuple.w * scalar);
}

using namespace raytracer;

Tuple Tuple::point(double x, double y, double z)
{
    return Tuple(x, y, z, 1.0);
}

Tuple Tuple::vector(double x, double y, double z)
{
    return Tuple(x, y, z, 0.0);
}

Tuple::Tuple(double x, double y, double z, double w)
    : x(x), y(y), z(z), w(w)
{
}

bool Tuple::isPoint() const
{
    return w == 1.0;
}

Point Tuple::asPoint() const
{
    if (!isPoint())
        throw std::runtime_error("Tuple is not a point");
    return Point(x, y, z);
}

bool Tuple::isVector() const
{
    return w == 0.0;
}

Vector Tuple::asVector() const
{
    if (!isVector())
        throw std::runtime_error("Tuple is not a vector");
    return Vector(x, y, z);
}

Tuple Tuple::operator+(const Tuple &other) const
{
    return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}

Tuple Tuple::operator-(const Tuple &other) const
{
    return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}

bool Tuple::operator==(const Tuple &other) const
{
    return double_equals(x, other.x) && double_equals(y, other.y) && double_equals(z, other.z) && double_equals(w, other.w);
}

Tuple Tuple::operator-() const
{
    return Tuple(-x, -y, -z, -w);
}

Tuple Tuple::operator*(double scalar) const
{
    return Tuple(x * scalar, y * scalar, z * scalar, w * scalar);
}

Tuple Tuple::operator/(double scalar) const
{
    return Tuple(x / scalar, y / scalar, z / scalar, w / scalar);
}

double &Tuple::operator[](int index)
{
    switch (index) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        throw std::out_of_range("Tuple index out of range");
    }
}

double Tuple::operator[](int index) const
{
    switch (index) {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    default:
        throw std::out_of_range("Tuple index out of range");
    }
}

double Tuple::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::normalize() const
{
    double mag = magnitude();
    return Tuple(x / mag, y / mag, z / mag, w / mag);
}

double Tuple::dot(const Tuple &other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Tuple Tuple::cross(const Tuple &other) const
{
    return Tuple(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0.0);
}

Tuple Tuple::reflect(const Tuple &normal) const
{
    return *this - normal * 2 * this->dot(normal);
}
