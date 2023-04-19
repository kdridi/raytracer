#include "raytracer.hpp"

#include <gmock/gmock.h>

class ConeTest : public testing::Test {};

// Intersecting a cone with a ray
TEST_F(ConeTest, Intersecting_a_cone_with_a_ray)
{
#define testWith(ray_origin, ray_direction, t0, t1)                                           \
    {                                                                                         \
        raytracer::Cone c;                                                                    \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        ASSERT_TRUE(xs.count() == 2);                                                         \
        EXPECT_TRUE(double_equals(xs[0].t(), t0));                                            \
        EXPECT_TRUE(double_equals(xs[1].t(), t1));                                            \
    }

    testWith((0, 0, -5), (0, 0, 1), 5, 5);
    testWith((0, 0, -5), (1, 1, 1), 8.66025, 8.66025);
    testWith((1, 1, -5), (-0.5, -1, 1), 4.55006, 49.44994);
#undef testWith
}

// Intersecting a cone with a ray parallel to one of its halves
TEST_F(ConeTest, Intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves)
{
    raytracer::Cone c;
    raytracer::Vector direction = raytracer::Vector(0, 1, 1).normalize().asVector();
    raytracer::Ray r(raytracer::Point(0, 0, -1), direction);
    raytracer::Intersections xs = c.localIntersect(r);
    ASSERT_TRUE(xs.count() == 1);
    EXPECT_TRUE(double_equals(xs[0].t(), 0.35355));
}

// Intersecting a cone's end caps
TEST_F(ConeTest, Intersecting_a_cones_end_caps)
{
#define testWith(ray_origin, ray_direction, n)                                                \
    {                                                                                         \
        raytracer::Cone c;                                                                    \
        c.minimum = -0.5;                                                                     \
        c.maximum = 0.5;                                                                      \
        c.closed = true;                                                                      \
        raytracer::Vector direction = raytracer::Vector ray_direction.normalize().asVector(); \
        raytracer::Ray r(raytracer::Point ray_origin, direction);                             \
        raytracer::Intersections xs = c.localIntersect(r);                                    \
        std::cout << "xs.count() = " << xs.count() << std::endl;                              \
        ASSERT_TRUE(xs.count() == n);                                                         \
    }

    // testWith((0, 0, -5), (0, 1, 0), 0);
    testWith((0, 0, -0.25), (0, 1, 1), 2);
    // testWith((0, 0, -0.25), (0, 1, 0), 4);
#undef testWith
}

// Computing the normal vector on a cone
TEST_F(ConeTest, Computing_the_normal_vector_on_a_cone)
{
#define testWith(point, normal)                                        \
    {                                                                  \
        raytracer::Cone c;                                             \
        raytracer::Vector n = c.localNormalAt(raytracer::Point point); \
        EXPECT_TRUE(n == raytracer::Vector normal);                    \
    }

    testWith((0, 0, 0), (0, 0, 0));
    testWith((1, 1, 1), (1, -std::sqrt(2), 1));
    testWith((-1, -1, 0), (-1, 1, 0));
#undef testWith
}
