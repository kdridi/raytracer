#include "sphere.hpp"
#include "intersections.hpp"
#include "ray.hpp"
#include "tuple.hpp"

using namespace raytracer;

Sphere::Sphere()
{
}

bool Sphere::operator==(const Sphere &other) const
{
    return m_transform == other.m_transform;
}

Intersections Sphere::localIntersect(const Ray &ray) const
{
    Tuple sphere_to_ray = ray.origin() - Tuple::point(0, 0, 0);
    double a = ray.direction().dot(ray.direction());
    double b = 2 * ray.direction().dot(sphere_to_ray);
    double c = sphere_to_ray.dot(sphere_to_ray) - 1;
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return Intersections();
    } else {
        double t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2 * a);

        return Intersections({Intersection(t1, *this), Intersection(t2, *this)});
    }
}

Vector Sphere::localNormalAt(const Point &localPoint) const
{
    return (localPoint - Point(0, 0, 0)).asVector();
}

GlassSphere::GlassSphere() : Sphere()
{
    m_transform = Matrix::identity(4);
    m_material.transparency = 1.0;
    m_material.refractiveIndex = 1.5;
}
