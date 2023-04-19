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

// The normal on a sphere at a point on the x axis
TEST_F(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_x_axis)
{
    raytracer::Sphere s;
    raytracer::Tuple n = s.normalAt(raytracer::Point(1, 0, 0));
    EXPECT_TRUE(n == raytracer::Vector(1, 0, 0));
}

// The normal on a sphere at a point on the y axis
TEST_F(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_y_axis)
{
    raytracer::Sphere s;
    raytracer::Tuple n = s.normalAt(raytracer::Point(0, 1, 0));
    EXPECT_TRUE(n == raytracer::Vector(0, 1, 0));
}

// The normal on a sphere at a point on the z axis
TEST_F(SphereTest, The_normal_on_a_sphere_at_a_point_on_the_z_axis)
{
    raytracer::Sphere s;
    raytracer::Tuple n = s.normalAt(raytracer::Point(0, 0, 1));
    EXPECT_TRUE(n == raytracer::Vector(0, 0, 1));
}

// The normal on a sphere at a nonaxial point
TEST_F(SphereTest, The_normal_on_a_sphere_at_a_nonaxial_point)
{
    raytracer::Sphere s;
    raytracer::Tuple n = s.normalAt(raytracer::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    EXPECT_TRUE(n == raytracer::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

// The normal is a normalized vector
TEST_F(SphereTest, The_normal_is_a_normalized_vector)
{
    raytracer::Sphere s;
    raytracer::Tuple n = s.normalAt(raytracer::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    EXPECT_TRUE(n == n.normalize());
}

// Computing the normal on a translated sphere
TEST_F(SphereTest, Computing_the_normal_on_a_translated_sphere)
{
    raytracer::Sphere s;
    s.transform() = raytracer::Matrix::translation(0, 1, 0);
    raytracer::Tuple n = s.normalAt(raytracer::Point(0, 1.70711, -0.70711));
    EXPECT_TRUE(n == raytracer::Vector(0, 0.70711, -0.70711));
}

// Computing the normal on a transformed sphere
TEST_F(SphereTest, Computing_the_normal_on_a_transformed_sphere)
{
    raytracer::Sphere s;
    s.transform() = raytracer::Matrix::scaling(1, 0.5, 1) * raytracer::Matrix::rotationZ(M_PI / 5);
    raytracer::Tuple n = s.normalAt(raytracer::Point(0, sqrt(2) / 2, -sqrt(2) / 2));
    EXPECT_TRUE(n == raytracer::Vector(0, 0.97014, -0.24254));
}

// A sphere has a default material
TEST_F(SphereTest, A_sphere_has_a_default_material)
{
    raytracer::Sphere s;
    raytracer::Material m = s.material();
    EXPECT_TRUE(m == raytracer::Material());
}

// A sphere may be assigned a material
TEST_F(SphereTest, A_sphere_may_be_assigned_a_material)
{
    raytracer::Sphere s;
    raytracer::Material m;
    m.ambient() = 1;
    s.material() = m;
    EXPECT_TRUE(s.material() == m);
}

// A helper for producing a sphere with a glassy material
TEST_F(SphereTest, A_helper_for_producing_a_sphere_with_a_glassy_material)
{
    raytracer::GlassSphere s;
    EXPECT_TRUE(s.transform() == raytracer::Matrix::identity(4));
    EXPECT_TRUE(s.material().transparency == 1.0);
    EXPECT_TRUE(s.material().refractiveIndex == 1.5);
}
