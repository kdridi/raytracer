#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "tuple.hpp"

namespace raytracer {
    class Matrix;

    class Ray {
    public:
        Ray(const Tuple &, const Tuple &);
        virtual ~Ray() = default;

        Ray(const Ray &) = default;
        Ray &operator=(const Ray &) = default;

        Ray(Ray &&) = default;
        Ray &operator=(Ray &&) = default;

    public:
        Tuple origin() const;
        Tuple direction() const;
        Tuple position(double) const;
        Ray transform(const Matrix &) const;

    private:
        Tuple m_origin;
        Tuple m_direction;
    };

} // namespace raytracer

#endif // __RAY_HPP__
