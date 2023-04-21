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

Group *Group::CreateOctreeGroup(std::vector<Shape *> &shapes, int depth)
{
    if (shapes.empty())
        return nullptr;

    auto group = new Group();

    if (depth <= 0) {
        for (auto &shape : shapes)
            group->add(shape);
        return group;
    }

    // calculate bounds
    Bounds bounds(shapes.back()->bounds());
    for (auto &shape : shapes)
        bounds += shape->bounds();

    // calculate center
    auto center = bounds.center();

    std::vector<Shape *> subShapes[8];
    for (auto &shape : shapes) {
        auto shapeBounds = shape->bounds();
        auto shapeCenter = shapeBounds.center();

        int index = 0;
        if (shapeCenter.x > center.x)
            index |= 1;
        if (shapeCenter.y > center.y)
            index |= 2;
        if (shapeCenter.z > center.z)
            index |= 4;

        subShapes[index].push_back(shape);
    }

    for (int i = 0; i < 8; ++i) {
        auto subGroup = CreateOctreeGroup(subShapes[i], depth - 1);
        if (subGroup)
            group->add(subGroup);
    }

    return group;
}

Group::Group()
    : AShape()
{
}

Group::~Group()
{
    while (!empty())
        remove(&(*this)[0]);
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
