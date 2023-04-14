#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "utils.hpp"

namespace raytracer {
    class Color {
    public:
        Color(double red, double green, double blue);
        virtual ~Color() = default;

        Color(const Color &) = default;
        Color &operator=(const Color &) = default;

        Color(Color &&) = default;
        Color &operator=(Color &&) = default;

    public:
        bool operator==(const Color &) const;
        Color operator+(const Color &) const;
        Color operator-(const Color &) const;
        Color operator*(const Color &) const;
        Color operator*(double) const;

    public:
        double red() const;
        double green() const;
        double blue() const;

    private:
        double m_red;
        double m_green;
        double m_blue;
    };

} // namespace raytracer

std::ostream &operator<<(std::ostream &, const raytracer::Color &);
raytracer::Color operator*(double, const raytracer::Color &);

#endif // __COLOR_HPP__