#include "raytracer.hpp"

using namespace raytracer;

Cylinder::Cylinder()
    : minimum(-std::numeric_limits<double>::infinity()), maximum(std::numeric_limits<double>::infinity()), closed(false)
{
}

Intersections Cylinder::localIntersect(const Ray &r) const
{
    std::vector<Intersection> xs;
    intersectCaps(r, xs);

    auto d = r.direction();
    auto o = r.origin();

    double a = d.x * d.x + d.z * d.z;
    double b = 2 * o.x * d.x + 2 * o.z * d.z;
    double c = o.x * o.x + o.z * o.z - 1;

    if (double_equals(a, 0))
        return xs;

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return xs;

    double t0 = (-b - sqrt(discriminant)) / (2 * a);
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    if (t0 > t1)
        std::swap(t0, t1);

    double y0 = o.y + t0 * d.y;
    if (minimum < y0 && y0 < maximum)
        xs.push_back(Intersection(t0, *this));

    double y1 = o.y + t1 * d.y;
    if (minimum < y1 && y1 < maximum)
        xs.push_back(Intersection(t1, *this));

    return Intersections(xs);
}

Vector Cylinder::localNormalAt(const Point &p) const
{
    // compute the square of the distance from the y axis
    double dist = p.x * p.x + p.z * p.z;

    if (dist < 1 && p.y >= maximum - EPSILON)
        return Vector(0, 1, 0);

    if (dist < 1 && p.y <= minimum + EPSILON)
        return Vector(0, -1, 0);

    return Vector(p.x, 0, p.z);
}

bool Cylinder::checkCaps(const Ray &r, double t)
{
    auto d = r.direction();
    auto o = r.origin();

    double x = o.x + t * d.x;
    double y = o.y + t * d.y;
    double z = o.z + t * d.z;
    return (x * x + z * z) <= std::abs(1);
}

void Cylinder::intersectCaps(const Ray &r, std::vector<Intersection> &xs) const
{
    auto d = r.direction();
    auto o = r.origin();

    // caps only matter if the cylinder is closed, and might possibly be
    // intersected by the ray.
    if (!closed || double_equals(d.y, 0))
        return;

    // Check for an intersection with the lower end cap by intersecting
    // the ray with the plane at y=cylinder.minimum
    double t = (minimum - o.y) / d.y;
    if (checkCaps(r, t))
        xs.push_back(Intersection(t, *this));

    // Check for an intersection with the upper end cap by intersecting
    // the ray with the plane at y=cylinder.maximum
    t = (maximum - o.y) / d.y;
    if (checkCaps(r, t))
        xs.push_back(Intersection(t, *this));
}
