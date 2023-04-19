#include "intersections.hpp"
#include "ray.hpp"
#include "shape.hpp"

using namespace raytracer;

std::ostream &operator<<(std::ostream &os, const raytracer::Computations &comps)
{
    os << "Computations(n1: " << comps.n1 << ", n2: " << comps.n2 << ")";
    return os;
}

Computations::Computations(const Intersection &intersection, const Ray &ray)
    : t(intersection.t()), shape(intersection.shape()), point(ray.position(t).asPoint()), eyev((-ray.direction()).asVector()), normalv(shape.normalAt(point).asVector()), inside(false), overPoint((point + normalv * EPSILON).asPoint()), reflectv(ray.direction().reflect(normalv).asVector()), n1(0.0), n2(0.0), underPoint((point - normalv * EPSILON).asPoint())
{
    if (normalv.dot(eyev) < 0) {
        inside = true;
        normalv = (-normalv).asVector();
    }
    overPoint = (point + normalv * EPSILON).asPoint();
    underPoint = (point - normalv * EPSILON).asPoint();
}

double Computations::schlick() const
{
    // Find the cosine of the angle between the eye and normal vectors.
    double cos = eyev.dot(normalv);

    // Total internal reflection can only occur if n1 > n2.
    if (n1 > n2) {
        double n = n1 / n2;
        double sin2_t = n * n * (1.0 - cos * cos);
        if (sin2_t > 1.0)
            return 1.0;

        // Compute cos(theta_t) using trig identity.
        double cos_t = std::sqrt(1.0 - sin2_t);

        // When n1 > n2, use cos(theta_t) instead.
        cos = cos_t;
    }

    double r0 = (n1 - n2) / (n1 + n2);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cos, 5);
}

Intersection::Intersection(double t, const Shape &shape)
    : m_t(t), m_shape(&shape)
{
}

bool Intersection::operator==(const Intersection &other) const
{
    return m_t == other.m_t && &m_shape == &other.m_shape;
}

Computations Intersection::prepareComputations(const Ray &ray, const Intersections &xs) const
{
    Computations comps(*this, ray);
    std::vector<const Shape *> containers;

    const Intersection *hit = this;

    xs.forEachIntersection([&](const Intersection &i) {
        if (hit == &i)
            if (containers.empty())
                comps.n1 = 1.0;
            else
                comps.n1 = containers.back()->material().refractiveIndex;

        auto it = std::find(containers.begin(), containers.end(), &i.shape());
        if (it != containers.end())
            containers.erase(it);
        else
            containers.push_back(&i.shape());

        if (hit == &i)
            if (containers.empty())
                comps.n2 = 1.0;
            else
                comps.n2 = containers.back()->material().refractiveIndex;
    });

    return comps;
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

Intersections::Intersections(std::vector<Intersection> intersections)
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

void Intersections::forEachIntersection(std::function<void(const Intersection &)> f) const
{
    for (const auto &i : m_intersections)
        f(i);
}
