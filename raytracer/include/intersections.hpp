#ifndef __INTERSECTIONS_HPP__
#define __INTERSECTIONS_HPP__

#include "utils.hpp"

namespace raytracer {
    class Shape;

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

    public:
        double t() const;
        const Shape &shape() const;

    private:
        double m_t;
        const Shape &m_shape;
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

    private:
        std::vector<Intersection> m_intersections;
    };

} // namespace raytracer

#endif // __INTERSECTIONS_HPP__
