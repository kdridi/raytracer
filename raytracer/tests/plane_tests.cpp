#include "raytracer.hpp"

#include <gmock/gmock.h>

class PlaneTest : public testing::Test {};

// The normal of a plane is constant everywhere
TEST_F(PlaneTest, The_normal_of_a_plane_is_constant_everywhere)
{
    raytracer::Plane p;

    raytracer::Vector n1 = p.localNormalAt(raytracer::Point(0, 0, 0));
    raytracer::Vector n2 = p.localNormalAt(raytracer::Point(10, 0, -10));
    raytracer::Vector n3 = p.localNormalAt(raytracer::Point(-5, 0, 150));

    ASSERT_TRUE(n1 == raytracer::Vector(0, 1, 0));
    ASSERT_TRUE(n2 == raytracer::Vector(0, 1, 0));
    ASSERT_TRUE(n3 == raytracer::Vector(0, 1, 0));
}

// Intersect with a ray parallel to the plane
TEST_F(PlaneTest, Intersect_with_a_ray_parallel_to_the_plane)
{
    raytracer::Plane p;
    raytracer::Ray r(raytracer::Point(0, 10, 0), raytracer::Vector(0, 0, 1));

    raytracer::Intersections xs = p.localIntersect(r);

    ASSERT_TRUE(xs.count() == 0);
}

// Intersect with a coplanar ray
TEST_F(PlaneTest, Intersect_with_a_coplanar_ray)
{
    raytracer::Plane p;
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));

    raytracer::Intersections xs = p.localIntersect(r);

    ASSERT_TRUE(xs.count() == 0);
}

// A ray intersecting a plane from above
TEST_F(PlaneTest, A_ray_intersecting_a_plane_from_above)
{
    raytracer::Plane p;
    raytracer::Ray r(raytracer::Point(0, 1, 0), raytracer::Vector(0, -1, 0));

    raytracer::Intersections xs = p.localIntersect(r);

    ASSERT_TRUE(xs.count() == 1);
    ASSERT_TRUE(xs[0].t() == 1);
    ASSERT_TRUE(&xs[0].shape() == &p);
}

// A ray intersecting a plane from below
TEST_F(PlaneTest, A_ray_intersecting_a_plane_from_below)
{
    raytracer::Plane p;
    raytracer::Ray r(raytracer::Point(0, -1, 0), raytracer::Vector(0, 1, 0));

    raytracer::Intersections xs = p.localIntersect(r);

    ASSERT_TRUE(xs.count() == 1);
    ASSERT_TRUE(xs[0].t() == 1);
    ASSERT_TRUE(&xs[0].shape() == &p);
}
