#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "shape.hpp"

namespace raytracer {

    class Sphere : public AShape {
    public:
        Sphere();
        virtual ~Sphere() = default;

        Sphere(const Sphere &) = default;
        Sphere &operator=(const Sphere &) = default;

        Sphere(Sphere &&) = default;
        Sphere &operator=(Sphere &&) = default;

    public:
        bool operator==(const Sphere &) const;

    public:
        Intersections localIntersect(const Ray &) const override;
        Vector localNormalAt(const Point &) const override;
    };

} // namespace raytracer

#endif // __SPHERE_HPP__
