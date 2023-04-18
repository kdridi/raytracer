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

Intersections Sphere::intersect(const Ray &ray) const
{
    Ray object_ray = ray.transform(m_transform.inverse());
    Tuple sphere_to_ray = object_ray.origin() - Tuple::point(0, 0, 0);
    double a = object_ray.direction().dot(object_ray.direction());
    double b = 2 * object_ray.direction().dot(sphere_to_ray);
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

Tuple Sphere::normalAt(const Tuple &world_point) const
{
    Tuple object_point = m_transform.inverse() * world_point;
    Tuple object_normal = object_point - Tuple::point(0, 0, 0);
    Tuple world_normal = m_transform.inverse().transpose() * object_normal;
    world_normal[3] = 0;
    return world_normal.normalize();
}
