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

Color World::shadeHit(const Computations &comps, const Shape &shape) const
{
    bool shadowed = isShadowed(comps.overPoint);
    return comps.shape.material().lighting(shape, *light(), comps.point, comps.eyev, comps.normalv, shadowed);
}

Color World::colorAt(const Ray &ray) const
{
    auto xs = intersect(ray);
    auto hit = xs.hit();
    if (hit != nullptr) {
        auto comps = hit->prepareComputations(ray);
        return shadeHit(comps, hit->shape());
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