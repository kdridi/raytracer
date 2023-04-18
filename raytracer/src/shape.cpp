#include "shape.hpp"
#include "intersections.hpp"
#include "ray.hpp"

using namespace raytracer;

AShape::AShape()
    : m_transform(Matrix::identity(4))
{
}

const Matrix &AShape::transform() const
{
    return m_transform;
}

const Material &AShape::material() const
{
    return m_material;
}

Matrix &AShape::transform()
{
    return m_transform;
}

Material &AShape::material()
{
    return m_material;
}

// Intersections AShape::intersect(const Ray &ray) const
// {
//     Ray object_ray = ray.transform(m_transform.inverse());
//     return localIntersect(object_ray);
// }

Intersections AShape::intersect(const Ray &ray) const
{
    Ray localRay = ray.transform(m_transform.inverse());
    return localIntersect(localRay);
}

Tuple AShape::normalAt(const Tuple &world_point) const
{
    Point local_point = (m_transform.inverse() * world_point).asPoint();
    Vector local_normal = localNormalAt(local_point);
    Tuple world_normal = m_transform.inverse().transpose() * local_normal;
    world_normal.w = 0;
    return world_normal.normalize();
}
