#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include "tuple.hpp"

namespace raytracer {
    class Vector : public Tuple {
    public:
        Vector(double x, double y, double z);
        virtual ~Vector() = default;

        Vector(const Vector &);
        Vector &operator=(const Vector &);

        Vector(Vector &&);
        Vector &operator=(Vector &&);
    };
} // namespace raytracer

#endif // __VECTOR_HPP__
