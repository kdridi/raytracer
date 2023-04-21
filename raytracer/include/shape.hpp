#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "material.hpp"
#include "matrix.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace raytracer {
    class Intersections;

    class Bounds {
    public:
        Bounds(Point const &p)
            : min(p), max(p)
        {
        }

        Bounds(Point const &min, Point const &max)
            : min(min), max(min)
        {
            add(max);
        }

        Bounds &add(Point const &p)
        {
            min.x = std::min(min.x, p.x);
            min.y = std::min(min.y, p.y);
            min.z = std::min(min.z, p.z);

            max.x = std::max(max.x, p.x);
            max.y = std::max(max.y, p.y);
            max.z = std::max(max.z, p.z);

            return *this;
        }

        Bounds &operator+=(Point const &p)
        {
            return add(p);
        }

        Bounds &operator+=(Bounds const &b)
        {
            return add(b.min).add(b.max);
        }

        bool intersect(Ray const &r) const
        {
            auto o = r.origin();
            auto d = r.direction();

            double tmin = (min.x - o.x) / d.x;
            double tmax = (max.x - o.x) / d.x;

            if (tmin > tmax)
                std::swap(tmin, tmax);

            double tymin = (min.y - o.y) / d.y;
            double tymax = (max.y - o.y) / d.y;

            if (tymin > tymax)
                std::swap(tymin, tymax);

            if ((tmin > tymax) || (tymin > tmax))
                return false;

            if (tymin > tmin)
                tmin = tymin;

            if (tymax < tmax)
                tmax = tymax;

            double tzmin = (min.z - o.z) / d.z;
            double tzmax = (max.z - o.z) / d.z;

            if (tzmin > tzmax)
                std::swap(tzmin, tzmax);

            if ((tmin > tzmax) || (tzmin > tmax))
                return false;

            if (tzmin > tmin)
                tmin = tzmin;

            if (tzmax < tmax)
                tmax = tzmax;

            return true;
        }

        Point center() const
        {
            return ((min + max) / 2).asPoint();
        }

        Vector size() const
        {
            return (max - min).asVector();
        }

        Point min, max;
    };

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

        virtual Bounds bounds() const = 0;
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
