#include "material.hpp"
#include "lights.hpp"
#include "point.hpp"
#include "vector.hpp"

using namespace raytracer;

Material::Material()
    : m_color(Color::White()), m_ambient(0.1), m_diffuse(0.9), m_specular(0.9), m_shininess(200.0), pattern(nullptr), reflective(0.0), transparency(0.0), refractiveIndex(1.0)
{
}

Material::~Material()
{
    if (pattern != nullptr)
        delete pattern;
}

bool Material::operator==(const Material &other) const
{
    return m_color == other.m_color && double_equals(m_ambient, other.m_ambient) && double_equals(m_diffuse, other.m_diffuse) && double_equals(m_specular, other.m_specular) && double_equals(m_shininess, other.m_shininess);
}

Color &Material::color()
{
    return m_color;
}

double &Material::ambient()
{
    return m_ambient;
}

double &Material::diffuse()
{
    return m_diffuse;
}

double &Material::specular()
{
    return m_specular;
}

double &Material::shininess()
{
    return m_shininess;
}

Color Material::lighting(const Shape &shape, const PointLight &light, const Point &point, const Vector &eyev, const Vector &normalv, bool inShadow) const
{
    Color color = m_color;

    if (pattern != nullptr)
        color = pattern->patternAtShape(shape, point);

    // Combine the surface color with the light's color/intensity
    Color effective_color = color * light.intensity();

    // Find the direction to the light source
    Vector lightv = (light.position() - point).normalize().asVector();

    // Compute the ambient contribution
    Color ambient = effective_color * m_ambient;

    if (inShadow)
        return ambient;

    // Light_dot_normal represents the cosine of the angle between the light vector and the normal vector. A negative number means the light is on the other side of the surface.
    double light_dot_normal = lightv.dot(normalv);
    Color diffuse{0, 0, 0};
    Color specular{0, 0, 0};
    if (light_dot_normal < 0) {
        diffuse = Color::Black();
        specular = Color::Black();
    } else {
        // Compute the diffuse contribution
        diffuse = effective_color * m_diffuse * light_dot_normal;

        // Reflect_dot_eye represents the cosine of the angle between the reflection vector and the eye vector. A negative number means the light reflects away from the eye.
        Tuple reflectv = (-lightv).reflect(normalv);
        double reflect_dot_eye = reflectv.dot(eyev);
        if (reflect_dot_eye <= 0) {
            specular = Color::Black();
        } else {
            // Compute the specular contribution
            double factor = pow(reflect_dot_eye, m_shininess);
            specular = light.intensity() * m_specular * factor;
        }
    }

    // Add the three contributions together to get the final shading
    return ambient + diffuse + specular;
}
