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
        Shape() = default;
        virtual ~Shape() = default;

        Shape(const Shape &) = default;
        Shape &operator=(const Shape &) = default;

        Shape(Shape &&) = default;
        Shape &operator=(Shape &&) = default;

    public:
        virtual Intersections intersect(const Ray &) const = 0;
        virtual Tuple normalAt(const Tuple &) const = 0;
        virtual Point worldToObject(const Point &) const = 0;
        virtual Vector normalToWorld(const Vector &) const = 0;

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

        Intersections intersect(const Ray &) const final;
        Tuple normalAt(const Tuple &) const final;
        Point worldToObject(const Point &) const final;
        Vector normalToWorld(const Vector &) const final;

        Shape *parent = nullptr;

    protected:
        AShape();
        virtual ~AShape();

        AShape(const AShape &) = default;
        AShape &operator=(const AShape &) = default;

        AShape(AShape &&) = default;
        AShape &operator=(AShape &&) = default;

        virtual Intersections localIntersect(const Ray &) const = 0;
        virtual Vector localNormalAt(const Point &) const = 0;

    protected:
        Matrix m_transform;
        Material m_material;
    };

} // namespace raytracer

#endif // __SHAPE_HPP__
