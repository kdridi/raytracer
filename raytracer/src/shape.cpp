#include "shape.hpp"

using namespace raytracer;

AShape::AShape()
    : m_transform(Matrix::identity(4))
{
}

Matrix &AShape::transform()
{
    return m_transform;
}
