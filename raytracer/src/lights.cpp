#include "lights.hpp"

using namespace raytracer;

PointLight::PointLight(const Tuple &position, const Color &intensity)
    : m_position(position), m_intensity(intensity)
{
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
