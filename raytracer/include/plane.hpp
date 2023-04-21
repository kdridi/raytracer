#ifndef __PLANE_HPP__
#define __PLANE_HPP__

#include "shape.hpp"
#include "utils.hpp"

namespace raytracer {

    class Plane : public AShape {
    public:
        Plane();
        virtual ~Plane() = default;

        Plane(const Plane &) = default;
        Plane &operator=(const Plane &) = default;

        Plane(Plane &&) = default;
        Plane &operator=(Plane &&) = default;

    public:
        bool operator==(const Plane &) const;

    public:
        Intersections localIntersect(const Ray &) const override;
        Vector localNormalAt(const Point &) const override;
        Bounds bounds() const override;
    };

} // namespace raytracer

#endif // __PLANE_HPP__
