#include "raytracer.hpp"

using namespace raytracer;

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
    : p1(p1), p2(p2), p3(p3), e1((p2 - p1).asVector()), e2((p3 - p1).asVector()), normal(e2.cross(e1).normalize().asVector())
{
}

Intersections Triangle::localIntersect(const Ray &ray) const
{
    auto d = ray.direction();
    auto o = ray.origin();

    auto dir_cross_e2 = d.cross(e2);
    auto det = e1.dot(dir_cross_e2);
    if (std::abs(det) < EPSILON) {
        return Intersections();
    }
    auto f = 1 / det;
    auto p1_to_origin = o - p1;
    auto u = f * p1_to_origin.dot(dir_cross_e2);
    if (u < 0 || u > 1) {
        return Intersections();
    }
    auto origin_cross_e1 = p1_to_origin.cross(e1);
    auto v = f * d.dot(origin_cross_e1);
    if (v < 0 || (u + v) > 1) {
        return Intersections();
    }
    auto t = f * e2.dot(origin_cross_e1);
    return Intersections({Intersection(t, *this)});
}

Vector Triangle::localNormalAt(const Point &) const
{
    return normal;
}
