#include "raytracer.hpp"

#include <gmock/gmock.h>

class RayTest : public testing::Test {};

// Creating and querying a ray
TEST_F(RayTest, Creating_and_querying_a_ray)
{
    raytracer::Point origin(1, 2, 3);
    raytracer::Vector direction(4, 5, 6);
    raytracer::Ray r(origin, direction);
    EXPECT_TRUE(r.origin() == origin);
    EXPECT_TRUE(r.direction() == direction);
}

// Computing a point from a distance
TEST_F(RayTest, Computing_a_point_from_a_distance)
{
    raytracer::Point origin(2, 3, 4);
    raytracer::Vector direction(1, 0, 0);
    raytracer::Ray r(origin, direction);
    EXPECT_TRUE(r.position(0) == origin);
    EXPECT_TRUE(r.position(1) == raytracer::Point(3, 3, 4));
    EXPECT_TRUE(r.position(-1) == raytracer::Point(1, 3, 4));
    EXPECT_TRUE(r.position(2.5) == raytracer::Point(4.5, 3, 4));
}

// Translating a ray
TEST_F(RayTest, Translating_a_ray)
{
    raytracer::Ray r(raytracer::Point(1, 2, 3), raytracer::Vector(0, 1, 0));
    raytracer::Matrix m = raytracer::Matrix::translation(3, 4, 5);
    raytracer::Ray r2 = r.transform(m);
    EXPECT_TRUE(r2.origin() == raytracer::Point(4, 6, 8));
    EXPECT_TRUE(r2.direction() == raytracer::Vector(0, 1, 0));
}

// Scaling a ray
TEST_F(RayTest, Scaling_a_ray)
{
    raytracer::Ray r(raytracer::Point(1, 2, 3), raytracer::Vector(0, 1, 0));
    raytracer::Matrix m = raytracer::Matrix::scaling(2, 3, 4);
    raytracer::Ray r2 = r.transform(m);
    EXPECT_TRUE(r2.origin() == raytracer::Point(2, 6, 12));
    EXPECT_TRUE(r2.direction() == raytracer::Vector(0, 3, 0));
}
