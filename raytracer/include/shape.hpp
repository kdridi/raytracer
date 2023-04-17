#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "material.hpp"
#include "matrix.hpp"
#include "utils.hpp"

namespace raytracer {
    class Intersections;
    class Ray;

    class Shape {
    public:
        virtual Intersections intersect(const Ray &) const = 0;
        virtual Tuple normalAt(const Tuple &) const = 0;

    public:
        virtual const Matrix &transform() const = 0;
        virtual const Material &material() const = 0;

        virtual Matrix &transform() = 0;
        virtual Material &material() = 0;
    };

    class AShape : public Shape {
    public:
        virtual const Matrix &transform() const;
        virtual const Material &material() const;
        virtual Matrix &transform();
        virtual Material &material();

    protected:
        AShape();
        virtual ~AShape() = default;

        AShape(const AShape &) = default;
        AShape &operator=(const AShape &) = default;

        AShape(AShape &&) = default;
        AShape &operator=(AShape &&) = default;

    protected:
        Matrix m_transform;
        Material m_material;
    };

} // namespace raytracer

#endif // __SHAPE_HPP__
