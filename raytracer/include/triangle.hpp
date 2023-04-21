#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "point.hpp"
#include "shape.hpp"
#include "vector.hpp"

namespace raytracer {

    class Triangle : public AShape {
    public:
        Triangle(const Point &p1, const Point &p2, const Point &p3);
        virtual ~Triangle() = default;

        virtual Intersections localIntersect(const Ray &) const;
        virtual Vector localNormalAt(const Point &) const;
        virtual Bounds bounds() const;

        const Point p1;
        const Point p2;
        const Point p3;
        const Vector e1;
        const Vector e2;
        const Vector normal;
    };

} // namespace raytracer

#endif // __TRIANGLE_HPP__
