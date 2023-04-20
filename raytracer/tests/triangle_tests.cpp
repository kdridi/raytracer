#include "raytracer.hpp"

#include <gmock/gmock.h>

class TriangleTest : public ::testing::Test {};

// Constructing a triangle
TEST_F(TriangleTest, ConstructingATriangle)
{
    raytracer::Point p1(0, 1, 0);
    raytracer::Point p2(-1, 0, 0);
    raytracer::Point p3(1, 0, 0);
    raytracer::Triangle triangle(p1, p2, p3);
    ASSERT_TRUE(triangle.p1 == p1);
    ASSERT_TRUE(triangle.p2 == p2);
    ASSERT_TRUE(triangle.p3 == p3);
    ASSERT_TRUE(triangle.e1 == raytracer::Vector(-1, -1, 0));
    ASSERT_TRUE(triangle.e2 == raytracer::Vector(1, -1, 0));
    ASSERT_TRUE(triangle.normal == raytracer::Vector(0, 0, -1));
}

// Finding the normal on a triangle
TEST_F(TriangleTest, FindingTheNormalOnATriangle)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    ASSERT_TRUE(triangle.normalAt(raytracer::Point(0, 0.5, 0)) == triangle.normal);
    ASSERT_TRUE(triangle.normalAt(raytracer::Point(-0.5, 0.75, 0)) == triangle.normal);
    ASSERT_TRUE(triangle.normalAt(raytracer::Point(0.5, 0.25, 0)) == triangle.normal);
}

// Intersecting a ray parallel to the triangle
TEST_F(TriangleTest, IntersectingARayParallelToTheTriangle)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    raytracer::Ray ray(raytracer::Point(0, -1, -2), raytracer::Vector(0, 1, 0));
    ASSERT_TRUE(triangle.intersect(ray).count() == 0);
}

// A ray misses the p1-p3 edge
TEST_F(TriangleTest, ARayMissesTheP1P3Edge)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    raytracer::Ray ray(raytracer::Point(1, 1, -2), raytracer::Vector(0, 0, 1));
    ASSERT_TRUE(triangle.intersect(ray).count() == 0);
}

// A ray misses the p1-p2 edge
TEST_F(TriangleTest, ARayMissesTheP1P2Edge)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    raytracer::Ray ray(raytracer::Point(-1, 1, -2), raytracer::Vector(0, 0, 1));
    ASSERT_TRUE(triangle.intersect(ray).count() == 0);
}

// A ray misses the p2-p3 edge
TEST_F(TriangleTest, ARayMissesTheP2P3Edge)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    raytracer::Ray ray(raytracer::Point(0, -1, -2), raytracer::Vector(0, 0, 1));
    ASSERT_TRUE(triangle.intersect(ray).count() == 0);
}

// A ray strikes a triangle
TEST_F(TriangleTest, ARayStrikesATriangle)
{
    raytracer::Triangle triangle(raytracer::Point(0, 1, 0), raytracer::Point(-1, 0, 0), raytracer::Point(1, 0, 0));
    raytracer::Ray ray(raytracer::Point(0, 0.5, -2), raytracer::Vector(0, 0, 1));
    auto xs = triangle.intersect(ray);
    ASSERT_TRUE(xs.count() == 1);
    ASSERT_TRUE(double_equals(xs[0].t(), 2));
}
