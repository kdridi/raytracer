#include "tuple.hpp"

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

Tuple::Tuple(double x, double y, double z, double w)
    : x(x), y(y), z(z), w(w)
{
}

bool Tuple::isPoint() const
{
    return w == 1.0;
}

bool Tuple::isVector() const
{
    return w == 0.0;
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
    return x == other.x && y == other.y && z == other.z && w == other.w;
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
