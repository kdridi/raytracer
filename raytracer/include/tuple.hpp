#ifndef __TUPLE_HPP__
#define __TUPLE_HPP__

#include "utils.hpp"

namespace raytracer {
    class Tuple {
    public:
        static Tuple point(double, double, double);
        static Tuple vector(double, double, double);

    public:
        Tuple(double x, double y, double z, double w);
        virtual ~Tuple() = default;

        Tuple(const Tuple &) = default;
        Tuple &operator=(const Tuple &) = default;

        Tuple(Tuple &&) = default;
        Tuple &operator=(Tuple &&) = default;

    public:
        bool isPoint() const;
        bool isVector() const;

    public:
        Tuple operator+(const Tuple &) const;
        Tuple operator-(const Tuple &) const;
        bool operator==(const Tuple &) const;
        Tuple operator-() const;
        Tuple operator*(double) const;
        Tuple operator/(double) const;
        double &operator[](int);
        double operator[](int) const;

    public:
        double magnitude() const;
        Tuple normalize() const;
        double dot(const Tuple &) const;
        Tuple cross(const Tuple &) const;

    public:
        double x, y, z, w;
    };

} // namespace raytracer

std::ostream &operator<<(std::ostream &, const raytracer::Tuple &);
raytracer::Tuple operator*(double, const raytracer::Tuple &);

#endif // __TUPLE_HPP__