#include "raytracer.hpp"

#include <gmock/gmock.h>

class CubeTest : public testing::Test {};

// A ray intersects a cube
TEST_F(CubeTest, A_ray_intersects_a_cube)
{
#define testWith(ray_origin, ray_direction, t0, t1)                                     \
    {                                                                                   \
        raytracer::Cube c;                                                              \
        raytracer::Ray r(raytracer::Point ray_origin, raytracer::Vector ray_direction); \
        raytracer::Intersections xs = c.localIntersect(r);                              \
        ASSERT_TRUE(xs.count() == 2);                                                   \
        ASSERT_TRUE(xs[0].t() == t0);                                                   \
        ASSERT_TRUE(&xs[0].shape() == &c);                                              \
        ASSERT_TRUE(xs[1].t() == t1);                                                   \
        ASSERT_TRUE(&xs[1].shape() == &c);                                              \
    }

    testWith((5, 0.5, 0), (-1, 0, 0), 4, 6);
    testWith((-5, 0.5, 0), (1, 0, 0), 4, 6);
    testWith((0.5, 5, 0), (0, -1, 0), 4, 6);
    testWith((0.5, -5, 0), (0, 1, 0), 4, 6);
    testWith((0.5, 0, 5), (0, 0, -1), 4, 6);
    testWith((0.5, 0, -5), (0, 0, 1), 4, 6);
    testWith((0, 0.5, 0), (0, 0, 1), -1, 1);
#undef testWith
}

// A ray misses a cube
TEST_F(CubeTest, A_ray_misses_a_cube)
{
#define testWith(ray_origin, ray_direction)                                             \
    {                                                                                   \
        raytracer::Cube c;                                                              \
        raytracer::Ray r(raytracer::Point ray_origin, raytracer::Vector ray_direction); \
        raytracer::Intersections xs = c.localIntersect(r);                              \
        ASSERT_TRUE(xs.count() == 0);                                                   \
    }

    testWith((-2, 0, 0), (0.2673, 0.5345, 0.8018));
    testWith((0, -2, 0), (0.8018, 0.2673, 0.5345));
    testWith((0, 0, -2), (0.5345, 0.8018, 0.2673));
    testWith((2, 0, 2), (0, 0, -1));
    testWith((0, 2, 2), (0, -1, 0));
    testWith((2, 2, 0), (-1, 0, 0));
#undef testWith
}

// The normal on the surface of a cube
TEST_F(CubeTest, The_normal_on_the_surface_of_a_cube)
{
#define testWith(point, normal)                                        \
    {                                                                  \
        raytracer::Cube c;                                             \
        raytracer::Vector n = c.localNormalAt(raytracer::Point point); \
        ASSERT_TRUE(n == raytracer::Vector normal);                    \
    }

    testWith((1, 0.5, -0.8), (1, 0, 0));
    testWith((-1, -0.2, 0.9), (-1, 0, 0));
    testWith((-0.4, 1, -0.1), (0, 1, 0));
    testWith((0.3, -1, -0.7), (0, -1, 0));
    testWith((-0.6, 0.3, 1), (0, 0, 1));
    testWith((0.4, 0.4, -1), (0, 0, -1));
    testWith((1, 1, 1), (1, 0, 0));
    testWith((-1, -1, -1), (-1, 0, 0));
#undef testWith
}
