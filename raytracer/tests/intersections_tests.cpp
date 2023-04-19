#include "raytracer.hpp"

#include <gmock/gmock.h>

class IntersectionsTest : public testing::Test {};

// An intersection encapsulates t and object
TEST_F(IntersectionsTest, An_intersection_encapsulates_t_and_object)
{
    raytracer::Sphere s;
    raytracer::Intersection i(3.5, s);
    EXPECT_TRUE(double_equals(i.t(), 3.5));
    EXPECT_TRUE(&i.shape() == &s);
}

// Aggregating intersections
TEST_F(IntersectionsTest, Aggregating_intersections)
{
    raytracer::Sphere s;
    raytracer::Intersection i1(1, s);
    raytracer::Intersection i2(2, s);
    raytracer::Intersections xs({i1, i2});
    EXPECT_EQ(xs.count(), 2);
    EXPECT_TRUE(double_equals(xs[0].t(), 1));
    EXPECT_TRUE(double_equals(xs[1].t(), 2));
}

// The hit, when all intersections have positive t
TEST_F(IntersectionsTest, The_hit_when_all_intersections_have_positive_t)
{
    raytracer::Sphere s;
    raytracer::Intersection i1(1, s);
    raytracer::Intersection i2(2, s);
    raytracer::Intersections xs({i1, i2});
    EXPECT_TRUE(&xs.hit()->shape() == &s);
    EXPECT_TRUE(double_equals(xs.hit()->t(), 1));
}

// The hit, when some intersections have negative t
TEST_F(IntersectionsTest, The_hit_when_some_intersections_have_negative_t)
{
    raytracer::Sphere s;
    raytracer::Intersection i1(-1, s);
    raytracer::Intersection i2(1, s);
    raytracer::Intersections xs({i1, i2});
    EXPECT_TRUE(&xs.hit()->shape() == &s);
    EXPECT_TRUE(double_equals(xs.hit()->t(), 1));
}

// The hit, when all intersections have negative t
TEST_F(IntersectionsTest, The_hit_when_all_intersections_have_negative_t)
{
    raytracer::Sphere s;
    raytracer::Intersection i1(-2, s);
    raytracer::Intersection i2(-1, s);
    raytracer::Intersections xs({i1, i2});
    EXPECT_TRUE(xs.hit() == nullptr);
}

// The hit is always the lowest nonnegative intersection
TEST_F(IntersectionsTest, The_hit_is_always_the_lowest_nonnegative_intersection)
{
    raytracer::Sphere s;
    raytracer::Intersection i1(5, s);
    raytracer::Intersection i2(7, s);
    raytracer::Intersection i3(-3, s);
    raytracer::Intersection i4(2, s);
    raytracer::Intersections xs({i1, i2, i3, i4});
    EXPECT_TRUE(&xs.hit()->shape() == &s);
    EXPECT_TRUE(double_equals(xs.hit()->t(), 2));
}

// Precomputing the state of an intersection
TEST_F(IntersectionsTest, Precomputing_the_state_of_an_intersection)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    raytracer::Intersection i(4, s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_TRUE(double_equals(comps.t, i.t()));
    EXPECT_TRUE(&comps.shape == &i.shape());
    EXPECT_TRUE(comps.point == raytracer::Point(0, 0, -1));
    EXPECT_TRUE(comps.eyev == raytracer::Vector(0, 0, -1));
    EXPECT_TRUE(comps.normalv == raytracer::Vector(0, 0, -1));
}

// The hit, when an intersection occurs on the outside
TEST_F(IntersectionsTest, The_hit_when_an_intersection_occurs_on_the_outside)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    raytracer::Intersection i(4, s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_FALSE(comps.inside);
}

// The hit, when an intersection occurs on the inside
TEST_F(IntersectionsTest, The_hit_when_an_intersection_occurs_on_the_inside)
{
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    raytracer::Intersection i(1, s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_TRUE(comps.point == raytracer::Point(0, 0, 1));
    EXPECT_TRUE(comps.eyev == raytracer::Vector(0, 0, -1));
    EXPECT_TRUE(comps.inside);
    // normal would have been (0, 0, 1), but is inverted!
    EXPECT_TRUE(comps.normalv == raytracer::Vector(0, 0, -1));
}

// The hit should offset the point
TEST_F(IntersectionsTest, The_hit_should_offset_the_point)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Sphere s;
    s.transform() = raytracer::Matrix::translation(0, 0, 1);
    raytracer::Intersection i(5, s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_TRUE(comps.overPoint.z < -EPSILON / 2);
    EXPECT_TRUE(comps.point.z > comps.overPoint.z);
}

// Precomputing the reflection vector
TEST_F(IntersectionsTest, Precomputing_the_reflection_vector)
{
    raytracer::Plane p;
    raytracer::Ray r(raytracer::Point(0, 1, -1), raytracer::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    raytracer::Intersection i(sqrt(2), p);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_TRUE(comps.reflectv == raytracer::Vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

// Finding n1 and n2 at various intersections
TEST_F(IntersectionsTest, Finding_n1_and_n2_at_various_intersections)
{
    raytracer::GlassSphere A;
    A.transform() = raytracer::Matrix::scaling(2, 2, 2);
    A.material().refractiveIndex = 1.5;

    raytracer::GlassSphere B;
    B.transform() = raytracer::Matrix::translation(0, 0, -0.25);
    B.material().refractiveIndex = 2.0;

    raytracer::GlassSphere C;
    C.transform() = raytracer::Matrix::translation(0, 0, 0.25);
    C.material().refractiveIndex = 2.5;

    raytracer::Ray r(raytracer::Point(0, 0, -4), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs({raytracer::Intersection(2, A), raytracer::Intersection(2.75, B), raytracer::Intersection(3.25, C), raytracer::Intersection(4.75, B), raytracer::Intersection(5.25, C), raytracer::Intersection(6, A)});
    {
        raytracer::Computations comps = xs[0].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 1.0));
        EXPECT_TRUE(double_equals(comps.n2, 1.5));
    }
    {
        raytracer::Computations comps = xs[1].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 1.5));
        EXPECT_TRUE(double_equals(comps.n2, 2.0));
    }
    {
        raytracer::Computations comps = xs[2].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 2.0));
        EXPECT_TRUE(double_equals(comps.n2, 2.5));
    }
    {
        raytracer::Computations comps = xs[3].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 2.5));
        EXPECT_TRUE(double_equals(comps.n2, 2.5));
    }
    {
        raytracer::Computations comps = xs[4].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 2.5));
        EXPECT_TRUE(double_equals(comps.n2, 1.5));
    }
    {
        raytracer::Computations comps = xs[5].prepareComputations(r, xs);
        EXPECT_TRUE(double_equals(comps.n1, 1.5));
        EXPECT_TRUE(double_equals(comps.n2, 1.0));
    }
}

// The under point is offset below the surface
TEST_F(IntersectionsTest, The_under_point_is_offset_below_the_surface)
{
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::GlassSphere s;
    s.transform() = raytracer::Matrix::translation(0, 0, 1);
    raytracer::Intersection i(5, s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    EXPECT_TRUE(comps.underPoint.z > EPSILON / 2);
    EXPECT_TRUE(comps.point.z < comps.underPoint.z);
}

// The schlick approximation under total internal reflection
TEST_F(IntersectionsTest, The_schlick_approximation_under_total_internal_reflection)
{
    raytracer::GlassSphere s;
    raytracer::Ray r(raytracer::Point(0, 0, sqrt(2) / 2), raytracer::Vector(0, 1, 0));
    raytracer::Intersections xs({raytracer::Intersection(-sqrt(2) / 2, s), raytracer::Intersection(sqrt(2) / 2, s)});
    raytracer::Computations comps = xs[1].prepareComputations(r, xs);
    double reflectance = comps.schlick();
    EXPECT_TRUE(double_equals(reflectance, 1.0));
}

// The schlick approximation with a perpendicular viewing angle
TEST_F(IntersectionsTest, The_schlick_approximation_with_a_perpendicular_viewing_angle)
{
    raytracer::GlassSphere s;
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 1, 0));
    raytracer::Intersections xs({raytracer::Intersection(-1, s), raytracer::Intersection(1, s)});
    raytracer::Computations comps = xs[1].prepareComputations(r, xs);
    double reflectance = comps.schlick();
    EXPECT_TRUE(double_equals(reflectance, 0.04));
}

// The schlick approximation with small angle and n2 > n1
TEST_F(IntersectionsTest, The_schlick_approximation_with_small_angle_and_n2_greater_than_n1)
{
    raytracer::GlassSphere s;
    raytracer::Ray r(raytracer::Point(0, 0.99, -2), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs({raytracer::Intersection(1.8589, s)});
    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    double reflectance = comps.schlick();
    EXPECT_TRUE(double_equals(reflectance, 0.48873));
}
