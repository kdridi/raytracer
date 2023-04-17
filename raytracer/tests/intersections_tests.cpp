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
