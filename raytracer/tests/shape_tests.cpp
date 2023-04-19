#include "raytracer.hpp"

#include <gmock/gmock.h>

class TestShape : public raytracer::AShape {
public:
    TestShape()
        : savedRay(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 0))
    {
    }

    virtual raytracer::Intersections localIntersect(const raytracer::Ray &ray) const
    {
        const_cast<TestShape *>(this)->savedRay = ray;
        return raytracer::Intersections();
    }

    virtual raytracer::Vector localNormalAt(const raytracer::Point &point) const
    {
        return (point - raytracer::Point(0, 0, 0)).asVector();
    }

    raytracer::Ray savedRay;
};

class ShapeTest : public testing::Test {};

// The default transformation
TEST_F(ShapeTest, The_default_transformation)
{
    TestShape s;
    ASSERT_TRUE(s.transform() == raytracer::Matrix::identity(4));
}

// Assigning a transformation
TEST_F(ShapeTest, Assigning_a_transformation)
{
    TestShape s;
    s.transform() = raytracer::Matrix::translation(2, 3, 4);
    ASSERT_TRUE(s.transform() == raytracer::Matrix::translation(2, 3, 4));
}

// The default material
TEST_F(ShapeTest, The_default_material)
{
    TestShape s;
    ASSERT_TRUE(s.material() == raytracer::Material());
}

// Assigning a material
TEST_F(ShapeTest, Assigning_a_material)
{
    TestShape s;
    s.material().ambient() = 1;
    ASSERT_TRUE(s.material().ambient() == 1);
}

// Intersecting a scaled shape with a ray
TEST_F(ShapeTest, Intersecting_a_scaled_shape_with_a_ray)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    TestShape s;
    s.transform() = raytracer::Matrix::scaling(2, 2, 2);
    auto xs = s.intersect(r);
    ASSERT_TRUE(s.savedRay.origin() == raytracer::Point(0, 0, -2.5));
    ASSERT_TRUE(s.savedRay.direction() == raytracer::Vector(0, 0, 0.5));
}

// Intersecting a translated shape with a ray
TEST_F(ShapeTest, Intersecting_a_translated_shape_with_a_ray)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    TestShape s;
    s.transform() = raytracer::Matrix::translation(5, 0, 0);
    auto xs = s.intersect(r);
    ASSERT_TRUE(s.savedRay.origin() == raytracer::Point(-5, 0, -5));
    ASSERT_TRUE(s.savedRay.direction() == raytracer::Vector(0, 0, 1));
}

// Computing the normal on a translated shape
TEST_F(ShapeTest, Computing_the_normal_on_a_translated_shape)
{
    TestShape s;
    s.transform() = raytracer::Matrix::translation(0, 1, 0);
    auto n = s.normalAt(raytracer::Point(0, 1.70711, -0.70711));
    ASSERT_TRUE(n == raytracer::Vector(0, 0.70711, -0.70711));
}

// Computing the normal on a transformed shape
TEST_F(ShapeTest, Computing_the_normal_on_a_transformed_shape)
{
    TestShape s;
    s.transform() = raytracer::Matrix::scaling(1, 0.5, 1) * raytracer::Matrix::rotationZ(M_PI / 5);
    auto n = s.normalAt(raytracer::Point(0, sqrt(2) / 2, -sqrt(2) / 2));
    ASSERT_TRUE(n == raytracer::Vector(0, 0.97014, -0.24254));
}

// A shape has a parent attribute
TEST_F(ShapeTest, A_shape_has_a_parent_attribute)
{
    TestShape s;
    ASSERT_TRUE(s.parent == nullptr);
}

// Converting a point from world to object space
TEST_F(ShapeTest, Converting_a_point_from_world_to_object_space)
{
    raytracer::Group g1;
    g1.transform() = raytracer::Matrix::rotationY(M_PI / 2);
    raytracer::Group *g2 = new raytracer::Group();
    g2->transform() = raytracer::Matrix::scaling(2, 2, 2);
    g1.add(g2);
    raytracer::Sphere *s = new raytracer::Sphere();
    s->transform() = raytracer::Matrix::translation(5, 0, 0);
    g2->add(s);
    auto p = s->worldToObject(raytracer::Point(-2, 0, -10));
    ASSERT_TRUE(p == raytracer::Point(0, 0, -1));
}

// Converting a normal from object to world space
TEST_F(ShapeTest, Converting_a_normal_from_object_to_world_space)
{
    raytracer::Group g1;
    g1.transform() = raytracer::Matrix::rotationY(M_PI / 2);
    raytracer::Group *g2 = new raytracer::Group();
    g2->transform() = raytracer::Matrix::scaling(1, 2, 3);
    g1.add(g2);
    raytracer::Sphere *s = new raytracer::Sphere();
    s->transform() = raytracer::Matrix::translation(5, 0, 0);
    g2->add(s);
    auto n = s->normalToWorld(raytracer::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_TRUE(n == raytracer::Vector(0.2857, 0.4286, -0.8571));
}

// Finding the normal on a child object
TEST_F(ShapeTest, Finding_the_normal_on_a_child_object)
{
    raytracer::Group g1;
    g1.transform() = raytracer::Matrix::rotationY(M_PI / 2);
    raytracer::Group *g2 = new raytracer::Group();
    g2->transform() = raytracer::Matrix::scaling(1, 2, 3);
    g1.add(g2);
    raytracer::Sphere *s = new raytracer::Sphere();
    s->transform() = raytracer::Matrix::translation(5, 0, 0);
    g2->add(s);
    auto n = s->normalAt(raytracer::Point(1.7321, 1.1547, -5.5774));
    ASSERT_TRUE(n == raytracer::Vector(0.2857, 0.4286, -0.8571));
}
