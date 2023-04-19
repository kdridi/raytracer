#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include "shape.hpp"

namespace raytracer {

    class Cube : public AShape {
    public:
        Cube() = default;
        virtual ~Cube() = default;

        virtual Intersections localIntersect(const Ray &r) const;
        virtual Vector localNormalAt(const Point &p) const;

    private:
        std::pair<double, double> checkAxis(double origin, double direction) const;
    };

} // namespace raytracer

#endif // __CUBE_HPP__