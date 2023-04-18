#include "intersections.hpp"
#include "ray.hpp"
#include "shape.hpp"

using namespace raytracer;

Computations::Computations(const Intersection &intersection, const Ray &ray)
    : t(intersection.t()), shape(intersection.shape()), point(ray.position(t).asPoint()), eyev((-ray.direction()).asVector()), normalv(shape.normalAt(point).asVector()), inside(false)
{
    if (normalv.dot(eyev) < 0) {
        inside = true;
        normalv = (-normalv).asVector();
    }
}

Intersection::Intersection(double t, const Shape &shape)
    : m_t(t), m_shape(&shape)
{
}

bool Intersection::operator==(const Intersection &other) const
{
    return m_t == other.m_t && &m_shape == &other.m_shape;
}

Computations Intersection::prepareComputations(const Ray &ray) const
{
    return Computations(*this, ray);
}

double Intersection::t() const
{
    return m_t;
}

const Shape &Intersection::shape() const
{
    return *m_shape;
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

Intersections &Intersections::add(const Intersections &other)
{
    for (const auto &i : other.m_intersections)
        m_intersections.push_back(i);
    return *this;
}

Intersections &Intersections::sort()
{
    typedef std::function<bool(const Intersection &, const Intersection &)> Compare;

    std::priority_queue<Intersection, std::vector<Intersection>, Compare> pq(
        [](const Intersection &a, const Intersection &b) {
            return a.t() > b.t();
        });

    while (m_intersections.empty() == false) {
        pq.push(m_intersections.back());
        m_intersections.pop_back();
    }

    while (pq.empty() == false) {
        m_intersections.push_back(pq.top());
        pq.pop();
    }

    return *this;
}
