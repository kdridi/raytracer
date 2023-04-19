#ifndef __CYLINDER_HPP__
#define __CYLINDER_HPP__

#include "shape.hpp"

namespace raytracer {
    class Intersection;

    class Cylinder : public AShape {
    public:
        Cylinder();
        virtual ~Cylinder() = default;

        virtual Intersections localIntersect(const Ray &r) const;
        virtual Vector localNormalAt(const Point &p) const;

        double minimum;
        double maximum;
        bool closed;

    private:
        static bool checkCaps(const Ray &r, double t);
        void intersectCaps(const Ray &r, std::vector<Intersection> &xs) const;
    };
} // namespace raytracer

#endif // __CYLINDER_HPP__
