#include "raytracer.hpp"

#include <gmock/gmock.h>

class PatternTest : public testing::Test {

public:
    PatternTest()
        : black(raytracer::Color(0, 0, 0)), white(raytracer::Color(1, 1, 1))
    {
    }

    void SetUp() override
    {
        black = raytracer::Color(0, 0, 0);
        white = raytracer::Color(1, 1, 1);
    }

    raytracer::Color black;
    raytracer::Color white;
};

// Creating a stripe pattern
TEST_F(PatternTest, Creating_a_stripe_pattern)
{
    raytracer::StripePattern p(black, white);

    ASSERT_TRUE(p.a == black);
    ASSERT_TRUE(p.b == white);
}

// A stripe pattern is constant in y
TEST_F(PatternTest, A_stripe_pattern_is_constant_in_y)
{
    raytracer::StripePattern p(black, white);

    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 1, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 2, 0)) == black);
}

// A stripe pattern is constant in z
TEST_F(PatternTest, A_stripe_pattern_is_constant_in_z)
{
    raytracer::StripePattern p(black, white);

    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 1)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 2)) == black);
}

// A stripe pattern alternates in x
TEST_F(PatternTest, A_stripe_pattern_alternates_in_x)
{
    raytracer::StripePattern p(black, white);

    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.9, 0, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(1, 0, 0)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(-0.1, 0, 0)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(-1, 0, 0)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(-1.1, 0, 0)) == black);
}

// Stripes with an object transformation
TEST_F(PatternTest, Stripes_with_an_object_transformation)
{
    raytracer::Sphere object;
    object.transform() = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::StripePattern pattern(white, black);
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(1.5, 0, 0));
    ASSERT_TRUE(c == white);
}

// Stripes with a pattern transformation
TEST_F(PatternTest, Stripes_with_a_pattern_transformation)
{
    raytracer::Sphere object;
    raytracer::StripePattern pattern(white, black);
    pattern.transform = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(1.5, 0, 0));
    ASSERT_TRUE(c == white);
}

// Stripes with both an object and a pattern transformation
TEST_F(PatternTest, Stripes_with_both_an_object_and_a_pattern_transformation)
{
    raytracer::Sphere object;
    object.transform() = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::StripePattern pattern(white, black);
    pattern.transform = raytracer::Matrix::translation(0.5, 0, 0);
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(2.5, 0, 0));
    ASSERT_TRUE(c == white);
}

class TestPattern : public raytracer::APattern {
public:
    TestPattern()
        : raytracer::APattern(raytracer::Color::White(), raytracer::Color::Black())
    {
    }

    raytracer::Color patternAt(const raytracer::Point &point) const override
    {
        return raytracer::Color(point.x, point.y, point.z);
    }
};

// The default pattern transformation
TEST_F(PatternTest, The_default_pattern_transformation)
{
    TestPattern pattern;
    ASSERT_TRUE(pattern.transform == raytracer::Matrix::identity(4));
}

// Assigning a transformation
TEST_F(PatternTest, Assigning_a_transformation)
{
    TestPattern pattern;
    pattern.transform = raytracer::Matrix::translation(1, 2, 3);
    ASSERT_TRUE(pattern.transform == raytracer::Matrix::translation(1, 2, 3));
}

// A pattern with an object transformation
TEST_F(PatternTest, A_pattern_with_an_object_transformation)
{
    raytracer::Sphere object;
    object.transform() = raytracer::Matrix::scaling(2, 2, 2);
    TestPattern pattern;
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(2, 3, 4));
    std::cout << "color: " << c << std::endl;
    ASSERT_TRUE(c == raytracer::Color(1, 1.5, 2));
}

// A pattern with a pattern transformation
TEST_F(PatternTest, A_pattern_with_a_pattern_transformation)
{
    raytracer::Sphere object;
    TestPattern pattern;
    pattern.transform = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(2, 3, 4));
    ASSERT_TRUE(c == raytracer::Color(1, 1.5, 2));
}

// A pattern with both an object and a pattern transformation
TEST_F(PatternTest, A_pattern_with_both_an_object_and_a_pattern_transformation)
{
    raytracer::Sphere object;
    object.transform() = raytracer::Matrix::scaling(2, 2, 2);
    TestPattern pattern;
    pattern.transform = raytracer::Matrix::translation(0.5, 1, 1.5);
    raytracer::Color c = pattern.patternAtShape(object, raytracer::Point(2.5, 3, 3.5));
    ASSERT_TRUE(c == raytracer::Color(0.75, 0.5, 0.25));
}

// A gradient linearly interpolates between colors
TEST_F(PatternTest, A_gradient_linearly_interpolates_between_colors)
{
    raytracer::GradientPattern p(white, black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 0)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.25, 0, 0)) == raytracer::Color(0.75, 0.75, 0.75));
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.50, 0, 0)) == raytracer::Color(0.50, 0.50, 0.50));
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.75, 0, 0)) == raytracer::Color(0.25, 0.25, 0.25));
}

// A ring should extend in both x and z
TEST_F(PatternTest, A_ring_should_extend_in_both_x_and_z)
{
    raytracer::RingPattern p(white, black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 0)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(1, 0, 0)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0, 0, 1)) == black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.708, 0, 0.708)) == black);
}

// Checkers should repeat in x
TEST_F(PatternTest, Checkers_should_repeat_in_x)
{
    raytracer::CheckersPattern p(white, black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.00, 0.00)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.99, 0.00, 0.00)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(1.01, 0.00, 0.00)) == black);
}

// Checkers should repeat in y
TEST_F(PatternTest, Checkers_should_repeat_in_y)
{
    raytracer::CheckersPattern p(white, black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.00, 0.00)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.99, 0.00)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 1.01, 0.00)) == black);
}

// Checkers should repeat in z
TEST_F(PatternTest, Checkers_should_repeat_in_z)
{
    raytracer::CheckersPattern p(white, black);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.00, 0.00)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.00, 0.99)) == white);
    ASSERT_TRUE(p.patternAt(raytracer::Point(0.00, 0.00, 1.01)) == black);
}
