#include "raytracer.hpp"

#include <gmock/gmock.h>

class SphereTest : public testing::Test {};

// A ray intersects a sphere at two points
TEST_F(SphereTest, A_ray_intersects_a_sphere_at_two_points)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), 4.0));
    EXPECT_TRUE(double_equals(xs[1].t(), 6.0));
}

// A ray intersects a sphere at a tangent
TEST_F(SphereTest, A_ray_intersects_a_sphere_at_a_tangent)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 1, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), 5.0));
    EXPECT_TRUE(double_equals(xs[1].t(), 5.0));
}

// A ray misses a sphere
TEST_F(SphereTest, A_ray_misses_a_sphere)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 2, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 0);
}

// A ray originates inside a sphere
TEST_F(SphereTest, A_ray_originates_inside_a_sphere)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), -1.0));
    EXPECT_TRUE(double_equals(xs[1].t(), 1.0));
}

// A sphere is behind a ray
TEST_F(SphereTest, A_sphere_is_behind_a_ray)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 0, 5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), -6.0));
    EXPECT_TRUE(double_equals(xs[1].t(), -4.0));
}

// Intersect sets the object on the intersection
TEST_F(SphereTest, Intersect_sets_the_object_on_the_intersection)
{
    raytracer::Sphere s;
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_EQ(&xs[0].shape(), &s);
    EXPECT_EQ(&xs[1].shape(), &s);
}

// A sphere's default transformation
TEST_F(SphereTest, A_spheres_default_transformation)
{
    raytracer::Sphere s;
    EXPECT_EQ(s.transform(), raytracer::Matrix::identity(4));
}

// Changing a sphere's transformation
TEST_F(SphereTest, Changing_a_spheres_transformation)
{
    raytracer::Sphere s;
    raytracer::Matrix t = raytracer::Matrix::translation(2, 3, 4);
    s.transform() = t;
    EXPECT_TRUE(s.transform() == t);
}

// Intersecting a scaled sphere with a ray
TEST_F(SphereTest, Intersecting_a_scaled_sphere_with_a_ray)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    s.transform() = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), 3));
    EXPECT_TRUE(double_equals(xs[1].t(), 7));
}

// Intersecting a translated sphere with a ray
TEST_F(SphereTest, Intersecting_a_translated_sphere_with_a_ray)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    s.transform() = raytracer::Matrix::translation(5, 0, 0);
    raytracer::Intersections xs = s.intersect(r);
    EXPECT_EQ(xs.count(), 0);
}
