#include "raytracer.hpp"

using namespace raytracer;

APattern::APattern(const Color &a, const Color &b)
    : a(a), b(b), transform(Matrix::identity(4))
{
}

Color APattern::patternAtShape(const Shape &shape, const Point &point) const
{
    Point objectPoint = (shape.transform().inverse() * point).asPoint();
    Point patternPoint = (transform.inverse() * objectPoint).asPoint();
    return patternAt(patternPoint);
}

StripePattern::StripePattern(const Color &a, const Color &b)
    : APattern(a, b)
{
}

Color StripePattern::patternAt(const Point &point) const
{
    if ((int)(std::floor(point.x)) % 2 == 0) {
        return a;
    } else {
        return b;
    }
}

GradientPattern::GradientPattern(const Color &a, const Color &b)
    : APattern(a, b)
{
}

Color GradientPattern::patternAt(const Point &point) const
{
    Color distance = b - a;
    double fraction = point.x - std::floor(point.x);
    return a + distance * fraction;
}

RingPattern::RingPattern(const Color &a, const Color &b)
    : APattern(a, b)
{
}

Color RingPattern::patternAt(const Point &point) const
{
    if ((int)(std::floor(std::sqrt(point.x * point.x + point.z * point.z))) % 2 == 0) {
        return a;
    } else {
        return b;
    }
}

CheckersPattern::CheckersPattern(const Color &a, const Color &b)
    : APattern(a, b)
{
}

Color CheckersPattern::patternAt(const Point &point) const
{
    if ((int)(std::floor(point.x) + std::floor(point.y) + std::floor(point.z)) % 2 == 0) {
        return a;
    } else {
        return b;
    }
}

PerlinPattern::PerlinPattern(const Color &a, const Color &b)
    : APattern(a, b)
{
}

#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

struct Point {
    double x, y, z;
};

class PerlinNoise {
public:
    PerlinNoise()
    {
        std::iota(p.begin(), p.end(), 0);
        std::shuffle(p.begin(), p.end(), std::default_random_engine());
        p.insert(p.end(), p.begin(), p.end());
    }

    double noise(const Tuple &point) const
    {
        int X = static_cast<int>(floor(point.x)) & 255;
        int Y = static_cast<int>(floor(point.y)) & 255;
        int Z = static_cast<int>(floor(point.z)) & 255;

        double x = point.x - floor(point.x);
        double y = point.y - floor(point.y);
        double z = point.z - floor(point.z);

        double u = fade(x);
        double v = fade(y);
        double w = fade(z);

        int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
        int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

        return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                    lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                         lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                              grad(p[BB + 1], x - 1, y - 1, z - 1))));
    }

private:
    static double fade(double t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static double lerp(double t, double a, double b)
    {
        return a + t * (b - a);
    }

    static double grad(int hash, double x, double y, double z)
    {
        int h = hash & 15;
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : h == 12 || h == 14 ? x
                                                  : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    std::vector<int> p = std::vector<int>(256);
};

Color PerlinPattern::patternAt(const Point &point) const
{
    PerlinNoise pn;
    return a + (b - a) * pn.noise(point);
}
