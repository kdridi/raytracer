#include "intersections.hpp"

using namespace raytracer;

Intersection::Intersection(double t, const Shape &shape)
    : m_t(t), m_shape(shape)
{
}

bool Intersection::operator==(const Intersection &other) const
{
    return m_t == other.m_t && &m_shape == &other.m_shape;
}

double Intersection::t() const
{
    return m_t;
}

const Shape &Intersection::shape() const
{
    return m_shape;
}

Intersections::Intersections()
{
}

Intersections::Intersections(std::initializer_list<Intersection> intersections)
    : m_intersections(intersections)
{
}

size_t Intersections::count() const
{
    return m_intersections.size();
}

const Intersection &Intersections::operator[](size_t index) const
{
    return m_intersections[index];
}

const Intersection *Intersections::hit() const
{
    const Intersection *hit = nullptr;
    for (const auto &i : m_intersections) {
        if (i.t() >= 0 && (!hit || i.t() < hit->t())) {
            hit = &i;
        }
    }
    return hit;
}
