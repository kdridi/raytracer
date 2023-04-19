#include "raytracer.hpp"

#include <gmock/gmock.h>

class CylinderTests : public testing::Test {};

// A ray misses a cylinder
TEST_F(CylinderTests, A_ray_misses_a_cylinder)
{
#define testWith(ray_origin, ray_direction)                                                   \
    {                                                                                         \
        raytracer::Cylinder c;                                                                \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        ASSERT_TRUE(xs.count() == 0);                                                         \
    }

    testWith((1, 0, 0), (0, 1, 0));
    testWith((0, 0, 0), (0, 1, 0));
    testWith((0, 0, -5), (1, 1, 1));
#undef testWith
}

// A ray strikes a cylinder
TEST_F(CylinderTests, A_ray_strikes_a_cylinder)
{
#define testWith(ray_origin, ray_direction, t0, t1)                                           \
    {                                                                                         \
        raytracer::Cylinder c;                                                                \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        ASSERT_TRUE(xs.count() == 2);                                                         \
        EXPECT_TRUE(double_equals(xs[0].t(), t0));                                            \
        EXPECT_TRUE(double_equals(xs[1].t(), t1));                                            \
    }

    testWith((1, 0, -5), (0, 0, 1), 5, 5);
    testWith((0, 0, -5), (0, 0, 1), 4, 6);
    testWith((0.5, 0, -5), (0.1, 1, 1), 6.80798, 7.08872);
#undef testWith
}

// The normal vector on a cylinder
TEST_F(CylinderTests, The_normal_vector_on_a_cylinder)
{
#define testWith(point, normal)                                        \
    {                                                                  \
        raytracer::Cylinder c;                                         \
        raytracer::Vector n = c.localNormalAt(raytracer::Point point); \
        EXPECT_TRUE(n == raytracer::Vector normal);                    \
    }

    testWith((1, 0, 0), (1, 0, 0));
    testWith((0, 5, -1), (0, 0, -1));
    testWith((0, -2, 1), (0, 0, 1));
    testWith((-1, 1, 0), (-1, 0, 0));
#undef testWith
}

// The default minimum and maximum for a cylinder
TEST_F(CylinderTests, The_default_minimum_and_maximum_for_a_cylinder)
{
    raytracer::Cylinder c;
    EXPECT_EQ(c.minimum, -std::numeric_limits<double>::infinity());
    EXPECT_EQ(c.maximum, std::numeric_limits<double>::infinity());
}

// Intersecting a constrained cylinder
TEST_F(CylinderTests, Intersecting_a_constrained_cylinder)
{
#define testWith(ray_origin, ray_direction, n)                                                \
    {                                                                                         \
        raytracer::Cylinder c;                                                                \
        c.minimum = 1;                                                                        \
        c.maximum = 2;                                                                        \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        ASSERT_TRUE(xs.count() == n);                                                         \
    }

    testWith((0, 1.5, 0), (0.1, 1, 0), 0);
    testWith((0, 3, -5), (0, 0, 1), 0);
    testWith((0, 0, -5), (0, 0, 1), 0);
    testWith((0, 2, -5), (0, 0, 1), 0);
    testWith((0, 1, -5), (0, 0, 1), 0);
    testWith((0, 1.5, -2), (0, 0, 1), 2);
#undef testWith
}

// The default closed value for a cylinder
TEST_F(CylinderTests, The_default_closed_value_for_a_cylinder)
{
    raytracer::Cylinder c;
    EXPECT_FALSE(c.closed);
}

// Intersecting the caps of a closed cylinder
TEST_F(CylinderTests, Intersecting_the_caps_of_a_closed_cylinder)
{
#define testWith(ray_origin, ray_direction, n)                                                \
    {                                                                                         \
        raytracer::Cylinder c;                                                                \
        c.minimum = 1;                                                                        \
        c.maximum = 2;                                                                        \
        c.closed = true;                                                                      \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        ASSERT_TRUE(xs.count() == n);                                                         \
    }

    testWith((0, 3, 0), (0, -1, 0), 2);
    testWith((0, 3, -2), (0, -1, 2), 2);
    testWith((0, 4, -2), (0, -1, 1), 2); // corner case
    testWith((0, 0, -2), (0, 1, 2), 2);
    testWith((0, -1, -2), (0, 1, 1), 2); // corner case
#undef testWith
}

// The normal vector on a cylinder's end caps
TEST_F(CylinderTests, The_normal_vector_on_a_cylinder_s_end_caps)
{
#define testWith(point, normal)                                        \
    {                                                                  \
        raytracer::Cylinder c;                                         \
        c.minimum = 1;                                                 \
        c.maximum = 2;                                                 \
        c.closed = true;                                               \
        raytracer::Vector n = c.localNormalAt(raytracer::Point point); \
        EXPECT_TRUE(n == raytracer::Vector normal);                    \
    }

    testWith((0, 1, 0), (0, -1, 0));
    testWith((0.5, 1, 0), (0, -1, 0));
    testWith((0, 1, 0.5), (0, -1, 0));
    testWith((0, 2, 0), (0, 1, 0));
    testWith((0.5, 2, 0), (0, 1, 0));
    testWith((0, 2, 0.5), (0, 1, 0));
#undef testWith
}
