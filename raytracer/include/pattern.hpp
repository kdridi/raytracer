#ifndef __PATTERN_HPP__
#define __PATTERN_HPP__

#include "color.hpp"
#include "matrix.hpp"
#include "utils.hpp"

namespace raytracer {
    class Point;
    class Shape;

    class APattern {
    public:
        virtual ~APattern() = default;

        APattern(const Color &a, const Color &b);
        Color patternAtShape(const Shape &, const Point &point) const;

    protected:
        virtual Color patternAt(const Point &point) const = 0;

    public:
        Color a;
        Color b;
        Matrix transform;
    };

    class StripePattern : public APattern {
    public:
        StripePattern(const Color &a, const Color &b);

        Color patternAt(const Point &point) const override;
    };

    class GradientPattern : public APattern {
    public:
        GradientPattern(const Color &a, const Color &b);

        Color patternAt(const Point &point) const override;
    };

    class RingPattern : public APattern {
    public:
        RingPattern(const Color &a, const Color &b);

        Color patternAt(const Point &point) const override;
    };

    class CheckersPattern : public APattern {
    public:
        CheckersPattern(const Color &a, const Color &b);

        Color patternAt(const Point &point) const override;
    };

    class PerlinPattern : public APattern {
    public:
        PerlinPattern(const Color &a, const Color &b);

        Color patternAt(const Point &point) const override;

    private:
        double noise(const Point &point) const;
    };

} // namespace raytracer

#endif // __PATTERN_HPP__
