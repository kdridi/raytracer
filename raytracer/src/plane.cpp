#include "raytracer.hpp"

using namespace raytracer;

Plane::Plane()
{
}

Intersections Plane::localIntersect(const Ray &ray) const
{
    if (double_equals(ray.direction().y, 0)) {
        return Intersections();
    }

    double t = -ray.origin().y / ray.direction().y;
    return Intersections({Intersection(t, *this)});
}

Vector Plane::localNormalAt(const Point &localPoint) const
{
    return Vector(0, 1, 0);
}
