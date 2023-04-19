#include "world.hpp"
#include "intersections.hpp"
#include "lights.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "sphere.hpp"

using namespace raytracer;

World World::Default()
{
    World world;
    world.light() = new PointLight(Point(-10, 10, -10), Color(1, 1, 1));

    Sphere *s1 = new Sphere();
    s1->material().color() = Color(0.8, 1.0, 0.6);
    s1->material().diffuse() = 0.7;
    s1->material().specular() = 0.2;
    world.shapes().push_back(s1);

    Sphere *s2 = new Sphere();
    s2->transform() = Matrix::scaling(0.5, 0.5, 0.5);
    world.shapes().push_back(s2);

    return world;
}

World::World()
    : m_shapes(), m_light(nullptr)
{
}

World::~World()
{
    for (auto shape : m_shapes)
        delete shape;
    delete m_light;
}

Intersections World::intersect(const Ray &ray) const
{
    Intersections xs;
    for (auto shape : m_shapes)
        xs.add(shape->intersect(ray));
    xs.sort();
    return xs;
}

Color World::shadeHit(const Computations &comps, int remaining) const
{
    bool shadowed = isShadowed(comps.overPoint);
    Color surface = comps.shape.material().lighting(comps.shape, *light(), comps.point, comps.eyev, comps.normalv, shadowed);
    Color reflected = reflectedColor(comps, remaining);
    Color refracted = refractedColor(comps, remaining);

    if (comps.shape.material().reflective > 0 && comps.shape.material().transparency > 0) {
        double reflectance = comps.schlick();
        return surface + reflected * reflectance + refracted * (1 - reflectance);
    }

    return surface + reflected + refracted;
}

Color World::colorAt(const Ray &ray, int remaining) const
{
    auto xs = intersect(ray);
    auto hit = xs.hit();
    if (hit != nullptr) {
        auto comps = hit->prepareComputations(ray, xs);
        return shadeHit(comps, remaining);
    }
    return Color(0, 0, 0);
}

bool World::isShadowed(const Point &point) const
{
    Vector v = (m_light->position() - point).asVector();
    double distance = v.magnitude();
    Vector direction = v.normalize().asVector();

    Ray r(point, direction);
    auto xs = intersect(r);
    auto h = xs.hit();
    if (h != nullptr && h->t() < distance)
        return true;
    return false;
}

Color World::reflectedColor(const Computations &comps, int remaining) const
{
    if (remaining <= 0)
        return Color(0, 0, 0);

    if (comps.shape.material().reflective == 0)
        return Color(0, 0, 0);

    Ray reflectRay(comps.overPoint, comps.reflectv);
    Color color = colorAt(reflectRay, remaining - 1) * comps.shape.material().reflective;
    return color;
}

Color World::refractedColor(const Computations &comps, int remaining) const
{
    if (remaining <= 0)
        return Color(0, 0, 0);

    if (comps.shape.material().transparency == 0)
        return Color(0, 0, 0);

    // Find the ratio of first index of refraction to the second.
    // (Yup, this is inverted from the definition of Snell's Law.)

    // std::cout << "comps: " << comps << std::endl;

    double n_ratio = comps.n1 / comps.n2;
    // std::cout << "n_ratio: " << n_ratio << std::endl;

    // cos(theta_i) is the same as the dot product of the two vectors
    double cos_i = comps.eyev.dot(comps.normalv);
    // std::cout << "cos_i: " << cos_i << std::endl;

    // Find sin(theta_t)^2 via trigonometric identity
    double sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
    // std::cout << "sin2_t: " << sin2_t << std::endl;

    if (sin2_t > 1)
        return Color(0, 0, 0);

    // Find cos(theta_t) via trigonometric identity
    double cos_t = sqrt(1.0 - sin2_t);

    // Compute the direction of the refracted ray
    Tuple direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;

    // Create the refracted ray
    Ray refractRay(comps.underPoint, direction);

    // Find the color of the refracted ray, making sure to multiply
    // by the transparency value to account for any opacity

    return colorAt(refractRay, remaining - 1) * comps.shape.material().transparency;
}
