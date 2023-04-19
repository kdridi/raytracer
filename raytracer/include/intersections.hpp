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

        Computations(const Computations &) = default;
        Computations &operator=(const Computations &) = default;

        Computations(Computations &&) = default;
        Computations &operator=(Computations &&) = default;

        double schlick() const;

        double t;
        const Shape &shape;
        Point point;
        Vector eyev;
        Vector normalv;
        bool inside;
        Point overPoint;
        Vector reflectv;
        double n1;
        double n2;
        Point underPoint;
    };

    class Intersections;

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
        Computations prepareComputations(const Ray &, const Intersections &) const;

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

        void forEachIntersection(std::function<void(const Intersection &)>) const;

    private:
        std::vector<Intersection> m_intersections;
    };

} // namespace raytracer

std::ostream &operator<<(std::ostream &, const raytracer::Computations &);

#endif // __INTERSECTIONS_HPP__
