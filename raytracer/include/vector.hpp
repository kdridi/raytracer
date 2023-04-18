#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "tuple.hpp"

namespace raytracer {
    class Vector : public Tuple {
    public:
        Vector(double x, double y, double z);
        virtual ~Vector() = default;

        Vector(const Vector &) = default;
        Vector &operator=(const Vector &) = default;

        Vector(Vector &&) = default;
        Vector &operator=(Vector &&) = default;
    };
} // namespace raytracer

#endif // __VECTOR_HPP__
