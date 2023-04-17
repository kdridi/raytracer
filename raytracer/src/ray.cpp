#include "ray.hpp"
#include "matrix.hpp"

using namespace raytracer;

Ray::Ray(const Tuple &origin, const Tuple &direction)
    : m_origin(origin), m_direction(direction)
{
}

Tuple Ray::origin() const
{
    return m_origin;
}

Tuple Ray::direction() const
{
    return m_direction;
}

Tuple Ray::position(double t) const
{
    return m_origin + t * m_direction;
}

Ray Ray::transform(const Matrix &m) const
{
    return Ray(m * m_origin, m * m_direction);
}
