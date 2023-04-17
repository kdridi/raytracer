#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "matrix.hpp"
#include "utils.hpp"

namespace raytracer {
    class Intersections;
    class Ray;

    class Shape {
    public:
        virtual Intersections intersect(const Ray &) const = 0;
    };

    class AShape : public Shape {
    public:
        Matrix &transform();

    protected:
        AShape();
        virtual ~AShape() = default;

        AShape(const AShape &) = default;
        AShape &operator=(const AShape &) = default;

        AShape(AShape &&) = default;
        AShape &operator=(AShape &&) = default;

    protected:
        Matrix m_transform;
    };

} // namespace raytracer

#endif // __SHAPE_HPP__
