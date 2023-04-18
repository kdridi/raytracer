#include "lights.hpp"

using namespace raytracer;

PointLight::PointLight(const Tuple &position, const Color &intensity)
    : m_position(position), m_intensity(intensity)
{
}

bool PointLight::operator==(const PointLight &other) const
{
    return m_position == other.m_position && m_intensity == other.m_intensity;
}

Tuple &PointLight::position()
{
    return m_position;
}

const Tuple &PointLight::position() const
{
    return m_position;
}

Color &PointLight::intensity()
{
    return m_intensity;
}

const Color &PointLight::intensity() const
{
    return m_intensity;
}
