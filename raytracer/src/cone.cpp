#include "raytracer.hpp"

using namespace raytracer;

Cone::Cone()
    : minimum(-std::numeric_limits<double>::infinity()), maximum(std::numeric_limits<double>::infinity()), closed(false)
{
}

Intersections Cone::localIntersect(const Ray &r) const
{
    auto d = r.direction();
    auto o = r.origin();

    double a = d.x * d.x - d.y * d.y + d.z * d.z;
    double b = 2 * o.x * d.x - 2 * o.y * d.y + 2 * o.z * d.z;

    if (double_equals(a, 0) && double_equals(b, 0)) {
        std::vector<Intersection> xs;
        intersectCaps(r, xs);
        return Intersections(xs);
    }

    double c = o.x * o.x - o.y * o.y + o.z * o.z;

    if (double_equals(a, 0) && !double_equals(b, 0)) {
        double t = -c / (2 * b);
        std::vector<Intersection> xs;
        xs.push_back(Intersection(t, *this));
        intersectCaps(r, xs);
        return Intersections(xs);
    }

    std::vector<Intersection> xs;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return Intersections();

    double t0 = (-b - std::sqrt(discriminant)) / (2 * a);
    double t1 = (-b + std::sqrt(discriminant)) / (2 * a);

    double y0 = r.position(t0).y;
    if (y0 < maximum && y0 > minimum)
        xs.emplace_back(t0, *this);

    double y1 = r.position(t1).y;
    if (y1 < maximum && y1 > minimum)
        xs.emplace_back(t1, *this);

    intersectCaps(r, xs);
    return Intersections(xs);
}

Vector Cone::localNormalAt(const Point &p) const
{
    double x = p.x, z = p.z;
    double dist = x * x + z * z;

    if (dist < 1 && p.y >= maximum - EPSILON)
        return Vector(0, 1, 0);

    if (dist < 1 && p.y <= minimum + EPSILON)
        return Vector(0, -1, 0);

    double y = std::sqrt(dist);
    if (p.y > 0)
        y = -y;
    return Vector(x, y, z);
}

bool Cone::checkCaps(const Ray &r, double t)
{
    auto i = r.position(t);
    double x = i.x, y = i.y, z = i.z;
    return (x * x + z * z) <= std::abs(y);
}

void Cone::intersectCaps(const Ray &r, std::vector<Intersection> &xs) const
{
    auto d = r.direction();
    auto o = r.origin();

    // caps only matter if the cone is closed, and might possibly be
    // intersected by the ray.
    if (!closed)
        return;

    // Check for an intersection with the lower end cap by intersecting
    // the ray with the plane at y=cone.minimum
    double t = (minimum - r.origin().y) / r.direction().y;
    if (checkCaps(r, t))
        xs.push_back(Intersection(t, *this));

    // Check for an intersection with the upper end cap by intersecting
    // the ray with the plane at y=cone.maximum
    t = (maximum - r.origin().y) / r.direction().y;
    if (checkCaps(r, t))
        xs.push_back(Intersection(t, *this));
}
