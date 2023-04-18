#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "color.hpp"

namespace raytracer {
    class Point;
    class PointLight;
    class Vector;

    class Material {
    public:
        Material();
        virtual ~Material() = default;

        Material(const Material &) = default;
        Material &operator=(const Material &) = default;

        Material(Material &&) = default;
        Material &operator=(Material &&) = default;

    public:
        bool operator==(const Material &) const;

    public:
        Color &color();
        double &ambient();
        double &diffuse();
        double &specular();
        double &shininess();

    public:
        Color lighting(const PointLight &light, const Point &point, const Vector &eyev, const Vector &normalv, bool inShadow = false) const;

    private:
        Color m_color;
        double m_ambient;
        double m_diffuse;
        double m_specular;
        double m_shininess;
    };

} // namespace raytracer

#endif // __MATERIAL_HPP__
