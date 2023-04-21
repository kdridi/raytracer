#include "raytracer.hpp"

using namespace raytracer;

Intersections Cube::localIntersect(const Ray &r) const
{

    auto [xtmin, xtmax] = checkAxis(r.origin().x, r.direction().x);
    auto [ytmin, ytmax] = checkAxis(r.origin().y, r.direction().y);
    auto [ztmin, ztmax] = checkAxis(r.origin().z, r.direction().z);

    auto tmin = std::max({xtmin, ytmin, ztmin});
    auto tmax = std::min({xtmax, ytmax, ztmax});

    if (tmin <= tmax) {
        auto xs = {
            Intersection(tmin, *this),
            Intersection(tmax, *this)};
        return Intersections(xs);
    }

    return Intersections();
}

Vector Cube::localNormalAt(const Point &p) const
{
    auto maxc = std::max({std::abs(p.x), std::abs(p.y), std::abs(p.z)});

    if (maxc == std::abs(p.x))
        return Vector(p.x, 0, 0);

    if (maxc == std::abs(p.y))
        return Vector(0, p.y, 0);

    return Vector(0, 0, p.z);
}

Bounds Cube::bounds() const
{
    return Bounds(Point(-1, -1, -1), Point(1, 1, 1));
}

std::pair<double, double> Cube::checkAxis(double origin, double direction) const
{
    auto tmin_numerator = 0 - 1 - origin;
    auto tmax_numerator = 0 + 1 - origin;

    double tmin, tmax;

    if (std::abs(direction) >= EPSILON) {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    } else {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax)
        std::swap(tmin, tmax);

    return {tmin, tmax};
}
