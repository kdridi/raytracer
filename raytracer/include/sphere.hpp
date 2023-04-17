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
        Intersections intersect(const Ray &) const override;
        Tuple normalAt(const Tuple &) const override;
    };

} // namespace raytracer

#endif // __SPHERE_HPP__
