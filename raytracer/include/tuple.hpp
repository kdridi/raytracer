#ifndef __TUPLE_HPP__
#define __TUPLE_HPP__

namespace raytracer {
    class Tuple {
    public:
        Tuple(double x, double y, double z, double w)
        : x(x), y(y), z(z), w(w) {
        }

        virtual ~Tuple() {
        }

        bool isPoint() const {
            return w == 1.0;
        }

        bool isVector() const {
            return w == 0.0;
        }

    public:
        double x, y, z, w;
    };
}

#endif // __TUPLE_HPP__