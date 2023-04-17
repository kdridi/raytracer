#include "raytracer.hpp"

#include <cmath>
#include <gmock/gmock.h>

class TupleTest : public testing::Test {};

// A tuple with w=1.0 is a point
TEST_F(TupleTest, A_tuple_with_w_1_is_a_point)
{
    raytracer::Tuple a(4.3, -4.2, 3.1, 1.0);
    EXPECT_EQ(a.x, 4.3);
    EXPECT_EQ(a.y, -4.2);
    EXPECT_EQ(a.z, 3.1);
    EXPECT_EQ(a.w, 1.0);
    EXPECT_TRUE(a.isPoint());
    EXPECT_FALSE(a.isVector());
}

// A tuple with w=0 is a vector
TEST_F(TupleTest, A_tuple_with_w_0_is_a_vector)
{
    raytracer::Tuple a(4.3, -4.2, 3.1, 0.0);
    EXPECT_EQ(a.x, 4.3);
    EXPECT_EQ(a.y, -4.2);
    EXPECT_EQ(a.z, 3.1);
    EXPECT_EQ(a.w, 0.0);
    EXPECT_FALSE(a.isPoint());
    EXPECT_TRUE(a.isVector());
}

// Point() creates tuples with w=1
TEST_F(TupleTest, Point_creates_tuples_with_w_1)
{
    raytracer::Point a(4, -4, 3);
    EXPECT_TRUE(a == raytracer::Tuple(4, -4, 3, 1));
}

// Vector() creates tuples with w=0
TEST_F(TupleTest, Vector_creates_tuples_with_w_0)
{
    raytracer::Vector a(4, -4, 3);
    EXPECT_TRUE(a == raytracer::Tuple(4, -4, 3, 0));
}

// Adding two tuples
TEST_F(TupleTest, Adding_two_tuples)
{
    raytracer::Tuple a1(3, -2, 5, 1);
    raytracer::Tuple a2(-2, 3, 1, 0);
    EXPECT_TRUE(a1 + a2 == raytracer::Tuple(1, 1, 6, 1));
}

// Subtracting two points
TEST_F(TupleTest, Subtracting_two_points)
{
    raytracer::Point p1(3, 2, 1);
    raytracer::Point p2(5, 6, 7);
    EXPECT_TRUE(p1 - p2 == raytracer::Vector(-2, -4, -6));
}

// Subtracting a vector from a point
TEST_F(TupleTest, Subtracting_a_vector_from_a_point)
{
    raytracer::Point p(3, 2, 1);
    raytracer::Vector v(5, 6, 7);
    EXPECT_TRUE(p - v == raytracer::Point(-2, -4, -6));
}

// Subtracting two vectors
TEST_F(TupleTest, Subtracting_two_vectors)
{
    raytracer::Vector v1(3, 2, 1);
    raytracer::Vector v2(5, 6, 7);
    EXPECT_TRUE(v1 - v2 == raytracer::Vector(-2, -4, -6));
}

// Subtracting a vector from the zero vector
TEST_F(TupleTest, Subtracting_a_vector_from_the_zero_vector)
{
    raytracer::Vector zero(0, 0, 0);
    raytracer::Vector v(1, -2, 3);
    EXPECT_TRUE(zero - v == raytracer::Vector(-1, 2, -3));
}

// Negating a tuple
TEST_F(TupleTest, Negating_a_tuple)
{
    raytracer::Tuple a(1, -2, 3, -4);
    EXPECT_TRUE(-a == raytracer::Tuple(-1, 2, -3, 4));
}

// Multiplying a tuple by a scalar
TEST_F(TupleTest, Multiplying_a_tuple_by_a_scalar)
{
    raytracer::Tuple a(1, -2, 3, -4);
    EXPECT_TRUE(a * 3.5 == raytracer::Tuple(3.5, -7, 10.5, -14));
    EXPECT_TRUE(3.5 * a == raytracer::Tuple(3.5, -7, 10.5, -14));
}

// Multiplying a tuple by a fraction
TEST_F(TupleTest, Multiplying_a_tuple_by_a_fraction)
{
    raytracer::Tuple a(1, -2, 3, -4);
    EXPECT_TRUE(a * 0.5 == raytracer::Tuple(0.5, -1, 1.5, -2));
    EXPECT_TRUE(0.5 * a == raytracer::Tuple(0.5, -1, 1.5, -2));
}

// Dividing a tuple by a scalar
TEST_F(TupleTest, Dividing_a_tuple_by_a_scalar)
{
    raytracer::Tuple a(1, -2, 3, -4);
    EXPECT_TRUE(a / 2 == raytracer::Tuple(0.5, -1, 1.5, -2));
}

// Computing the magnitude of vector(1, 0, 0)
TEST_F(TupleTest, Computing_the_magnitude_of_vector_1_0_0)
{
    raytracer::Vector v(1, 0, 0);
    EXPECT_EQ(v.magnitude(), 1);
}

// Computing the magnitude of vector(0, 1, 0)
TEST_F(TupleTest, Computing_the_magnitude_of_vector_0_1_0)
{
    raytracer::Vector v(0, 1, 0);
    EXPECT_EQ(v.magnitude(), 1);
}

// Computing the magnitude of vector(0, 0, 1)
TEST_F(TupleTest, Computing_the_magnitude_of_vector_0_0_1)
{
    raytracer::Vector v(0, 0, 1);
    EXPECT_EQ(v.magnitude(), 1);
}

// Computing the magnitude of vector(1, 2, 3)
TEST_F(TupleTest, Computing_the_magnitude_of_vector_1_2_3)
{
    raytracer::Vector v(1, 2, 3);
    EXPECT_EQ(v.magnitude(), std::sqrt(14));
}

// Computing the magnitude of vector(-1, -2, -3)
TEST_F(TupleTest, Computing_the_magnitude_of_vector_minus_1_minus_2_minus_3)
{
    raytracer::Vector v(-1, -2, -3);
    EXPECT_EQ(v.magnitude(), std::sqrt(14));
}

// Normalizing vector(4, 0, 0) gives (1, 0, 0)
TEST_F(TupleTest, Normalizing_vector_4_0_0_gives_1_0_0)
{
    raytracer::Vector v(4, 0, 0);
    EXPECT_TRUE(v.normalize() == raytracer::Vector(1, 0, 0));
}

// Normalizing vector(1, 2, 3)
TEST_F(TupleTest, Normalizing_vector_1_2_3)
{
    raytracer::Vector v(1, 2, 3);
    EXPECT_TRUE(v.normalize() == raytracer::Vector(1 / std::sqrt(14), 2 / std::sqrt(14), 3 / std::sqrt(14)));
}

// The magnitude of a normalized vector
TEST_F(TupleTest, The_magnitude_of_a_normalized_vector)
{
    raytracer::Vector v(1, 2, 3);
    EXPECT_EQ(v.normalize().magnitude(), 1);
}

// The dot product of two tuples
TEST_F(TupleTest, The_dot_product_of_two_tuples)
{
    raytracer::Vector a(1, 2, 3);
    raytracer::Vector b(2, 3, 4);
    EXPECT_EQ(a.dot(b), 20);
}

// The cross product of two vectors
TEST_F(TupleTest, The_cross_product_of_two_vectors)
{
    raytracer::Vector a(1, 2, 3);
    raytracer::Vector b(2, 3, 4);
    EXPECT_EQ(a.cross(b), raytracer::Vector(-1, 2, -1));
    EXPECT_EQ(b.cross(a), raytracer::Vector(1, -2, 1));
}

// Reflecting a vector approaching at 45°
TEST_F(TupleTest, Reflecting_a_vector_approaching_at_45_degrees)
{
    raytracer::Vector v(1, -1, 0);
    raytracer::Vector n(0, 1, 0);
    EXPECT_TRUE(v.reflect(n) == raytracer::Vector(1, 1, 0));
}

// Reflecting a vector off a slanted surface
TEST_F(TupleTest, Reflecting_a_vector_off_a_slanted_surface)
{
    raytracer::Vector v(0, -1, 0);
    raytracer::Vector n(std::sqrt(2) / 2, std::sqrt(2) / 2, 0);
    EXPECT_TRUE(v.reflect(n) == raytracer::Vector(1, 0, 0));
}
