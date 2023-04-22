#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "utils.hpp"

namespace raytracer {
    class Shape;
    class PointLight;
    class Intersections;
    class Computations;
    class Ray;
    class Color;
    class Point;

    class World {
    public:
        static World *Default();

    public:
        World();
        virtual ~World();

        World(const World &) = default;
        World &operator=(const World &) = default;

        World(World &&) = default;
        World &operator=(World &&) = default;

    public:
        std::vector<Shape *> &shapes() { return m_shapes; }
        const std::vector<Shape *> &shapes() const { return m_shapes; }

        PointLight *&light() { return m_light; }
        PointLight *const &light() const { return m_light; }

    public:
        Intersections intersect(const Ray &ray) const;
        Color shadeHit(const Computations &comps, int remaining = 5) const;
        Color colorAt(const Ray &ray, int remaining = 5) const;
        bool isShadowed(const Point &point) const;
        Color reflectedColor(const Computations &comps, int remaining = 5) const;
        Color refractedColor(const Computations &comps, int remaining = 5) const;

    private:
        std::vector<Shape *> m_shapes;
        PointLight *m_light;
    };

} // namespace raytracer

#endif // __WORLD_HPP__
