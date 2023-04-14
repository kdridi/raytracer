#include "color.hpp"

std::ostream &operator<<(std::ostream &os, const raytracer::Color &color)
{
    os << "Color(" << color.red() << ", " << color.green() << ", " << color.blue() << ")";
    return os;
}

raytracer::Color operator*(double scalar, const raytracer::Color &color)
{
    return color * scalar;
}

using namespace raytracer;

Color::Color(double red, double green, double blue)
    : m_red(red), m_green(green), m_blue(blue)
{
}

bool Color::operator==(const Color &other) const
{
    return double_equals(m_red, other.m_red) && double_equals(m_green, other.m_green) && double_equals(m_blue, other.m_blue);
}

Color Color::operator+(const Color &other) const
{
    return Color(m_red + other.m_red, m_green + other.m_green, m_blue + other.m_blue);
}

Color Color::operator-(const Color &other) const
{
    return Color(m_red - other.m_red, m_green - other.m_green, m_blue - other.m_blue);
}

Color Color::operator*(const Color &other) const
{
    return Color(m_red * other.m_red, m_green * other.m_green, m_blue * other.m_blue);
}

Color Color::operator*(double scalar) const
{
    return Color(m_red * scalar, m_green * scalar, m_blue * scalar);
}

double Color::red() const
{
    return m_red;
}

double Color::green() const
{
    return m_green;
}

double Color::blue() const
{
    return m_blue;
}
