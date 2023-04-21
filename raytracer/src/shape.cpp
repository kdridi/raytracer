#include "shape.hpp"
#include "intersections.hpp"
#include "ray.hpp"

using namespace raytracer;

AShape::AShape()
    : parent(nullptr), m_transform(Matrix::identity(4)), m_material(Material())
{
}

AShape::~AShape()
{
    if (parent) {
        delete parent;
        parent = nullptr;
    }
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
    Point local_point = worldToObject(world_point.asPoint());
    Vector local_normal = localNormalAt(local_point);
    Tuple world_normal = normalToWorld(local_normal);
    return world_normal;
}

Point AShape::worldToObject(const Point &world_point) const
{
    Point point = world_point;
    if (parent != nullptr)
        point = parent->worldToObject(point);

    return (m_transform.inverse() * point).asPoint();
}

Vector AShape::normalToWorld(const Vector &local_normal) const
{
    Tuple normal = (m_transform.inverse().transpose() * local_normal);
    normal.w = 0;
    normal = normal.normalize().asVector();

    if (parent != nullptr)
        normal = parent->normalToWorld(normal.asVector());

    return normal.asVector();
}
