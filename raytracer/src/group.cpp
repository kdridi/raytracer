#include "raytracer.hpp"

using namespace raytracer;

Shape *Group::Hexagon()
{
    auto hexagonSide = []() -> Shape * {
        auto hexagonCorner = []() -> Shape * {
            auto corner = new Sphere();
            corner->transform() = Matrix::translation(0, 0, -1) * Matrix::scaling(0.25, 0.25, 0.25);
            return corner;
        };

        auto hexagonEdge = []() -> Shape * {
            auto edge = new Cylinder();
            edge->minimum = 0;
            edge->maximum = 1;
            edge->transform() = Matrix::translation(0, 0, -1) * Matrix::rotationY(-M_PI / 6) * Matrix::rotationZ(-M_PI / 2) * Matrix::scaling(0.25, 1, 0.25);
            return edge;
        };

        auto side = new Group();
        side->add(hexagonCorner());
        side->add(hexagonEdge());
        return side;
    };

    auto hex = new Group();
    for (int i = 0; i < 6; ++i) {
        auto side = hexagonSide();
        side->transform() = Matrix::rotationY(i * M_PI / 3);
        hex->add(side);
    }

    return hex;
}

Group::Group()
    : AShape()
{
}

Group::~Group()
{
    while (m_shapes.size() > 0) {
        Shape *shape = m_shapes.back();
        m_shapes.pop_back();

        assert(shape != this);
        assert(shape != nullptr);
        delete shape;
    }
}

Intersections Group::localIntersect(const Ray &ray) const
{
    Intersections intersections;

    // check if the ray intersects the bounding box of the group
    // if (!bounds().intersect(ray))
    //     return intersections;

    for (const auto &shape : m_shapes)
        intersections += shape->intersect(ray);
    intersections.sort();
    return intersections;
}

Vector Group::localNormalAt(const Point &) const
{
    return Vector(0, 0, 0);
}

Bounds Group::bounds() const
{
    Bounds bounds = m_shapes[0]->bounds();
    for (const auto &shape : m_shapes)
        bounds += shape->bounds();
    return bounds;
}

void Group::add(Shape *shape)
{
    m_shapes.push_back(shape);
    reinterpret_cast<AShape *>(shape)->parent = this;
}

void Group::remove(Shape *shape)
{
    m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), shape), m_shapes.end());
    delete shape;
}

bool Group::empty() const
{
    return m_shapes.empty();
}

std::size_t Group::size() const
{
    return m_shapes.size();
}

Shape &Group::operator[](std::size_t index) const
{
    return *m_shapes[index];
}
