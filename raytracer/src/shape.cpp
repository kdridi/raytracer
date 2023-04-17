#include "shape.hpp"

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
