#ifndef __CONE_HPP__
#define __CONE_HPP__

#include "shape.hpp"

namespace raytracer {
    class Intersection;

    class Cone : public AShape {
    public:
        Cone();
        virtual ~Cone() {}

        virtual Intersections localIntersect(const Ray &r) const override;
        virtual Vector localNormalAt(const Point &p) const override;

        double minimum;
        double maximum;
        bool closed;

    private:
        static bool checkCaps(const Ray &r, double t);
        void intersectCaps(const Ray &r, std::vector<Intersection> &xs) const;
    };

} // namespace raytracer

#endif // __CONE_HPP__
