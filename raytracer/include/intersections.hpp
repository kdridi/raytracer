#ifndef __INTERSECTIONS_HPP__
#define __INTERSECTIONS_HPP__

#include "point.hpp"
#include "utils.hpp"
#include "vector.hpp"

namespace raytracer {
    class Shape;
    class Ray;
    class Intersection;

    struct Computations {
        Computations(const Intersection &intersection, const Ray &ray);

        double t;
        const Shape &shape;
        Point point;
        Vector eyev;
        Vector normalv;
        bool inside;
    };

    class Intersection {

    public:
        Intersection(double, const Shape &);
        virtual ~Intersection() = default;

        Intersection(const Intersection &) = default;
        Intersection &operator=(const Intersection &) = default;

        Intersection(Intersection &&) = default;
        Intersection &operator=(Intersection &&) = default;

    public:
        bool operator==(const Intersection &) const;
        Computations prepareComputations(const Ray &) const;

    public:
        double t() const;
        const Shape &shape() const;

    private:
        double m_t;
        const Shape *m_shape;
    };

    class Intersections {
    public:
        Intersections();
        Intersections(std::initializer_list<Intersection>);
        virtual ~Intersections() = default;

        Intersections(const Intersections &) = default;
        Intersections &operator=(const Intersections &) = default;

        Intersections(Intersections &&) = default;
        Intersections &operator=(Intersections &&) = default;

    public:
        size_t count() const;
        const Intersection &operator[](size_t) const;

    public:
        const Intersection *hit() const;
        Intersections &add(const Intersections &);
        Intersections &sort();

    private:
        std::vector<Intersection> m_intersections;
    };

} // namespace raytracer

#endif // __INTERSECTIONS_HPP__
