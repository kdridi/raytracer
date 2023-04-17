#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "tuple.hpp"

namespace raytracer {
    class Point : public Tuple {
    public:
        Point(double x, double y, double z);
        virtual ~Point() = default;

        Point(const Point &) = default;
        Point &operator=(const Point &) = default;

        Point(Point &&) = default;
        Point &operator=(Point &&) = default;
    };
} // namespace raytracer

#endif // __POINT_HPP__
