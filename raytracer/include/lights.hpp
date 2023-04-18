#ifndef __LIGHTS_HPP__
#define __LIGHTS_HPP__

#include "color.hpp"
#include "tuple.hpp"

namespace raytracer {

    class PointLight {
    public:
        PointLight(const Tuple &, const Color &);
        virtual ~PointLight() = default;

        PointLight(const PointLight &) = default;
        PointLight &operator=(const PointLight &) = default;

        PointLight(PointLight &&) = default;
        PointLight &operator=(PointLight &&) = default;

    public:
        bool operator==(const PointLight &) const;

    public:
        Tuple &position();
        const Tuple &position() const;
        Color &intensity();
        const Color &intensity() const;

    private:
        Tuple m_position;
        Color m_intensity;
    };

} // namespace raytracer

#endif // __LIGHTS_HPP__
