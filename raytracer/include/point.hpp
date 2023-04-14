#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "tuple.hpp"

namespace raytracer {
    class Point : public Tuple {
    public:
        Point(double x, double y, double z);
        virtual ~Point() = default;

        Point(const Point &);
        Point &operator=(const Point &);

        Point(Point &&);
        Point &operator=(Point &&);
    };
} // namespace raytracer

#endif // __POINT_HPP__
