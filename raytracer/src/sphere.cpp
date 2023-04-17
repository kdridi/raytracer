#include "sphere.hpp"
#include "intersections.hpp"
#include "ray.hpp"
#include "tuple.hpp"

using namespace raytracer;

Sphere::Sphere()
{
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
