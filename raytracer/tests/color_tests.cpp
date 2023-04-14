#include "raytracer.hpp"

#include <gmock/gmock.h>

class ColorTest : public testing::Test {};

// Colors are (red, green, blue) tuples
TEST_F(ColorTest, Colors_are_red_green_blue_tuples)
{
    raytracer::Color c(-0.5, 0.4, 1.7);
    EXPECT_EQ(c.red(), -0.5);
    EXPECT_EQ(c.green(), 0.4);
    EXPECT_EQ(c.blue(), 1.7);
}

// Adding colors
TEST_F(ColorTest, Adding_colors)
{
    raytracer::Color c1(0.9, 0.6, 0.75);
    raytracer::Color c2(0.7, 0.1, 0.25);
    EXPECT_EQ(c1 + c2, raytracer::Color(1.6, 0.7, 1.0));
}

// Subtracting colors
TEST_F(ColorTest, Subtracting_colors)
{
    raytracer::Color c1(0.9, 0.6, 0.75);
    raytracer::Color c2(0.7, 0.1, 0.25);
    EXPECT_EQ(c1 - c2, raytracer::Color(0.2, 0.5, 0.5));
}

// Multiplying a color by a scalar
TEST_F(ColorTest, Multiplying_a_color_by_a_scalar)
{
    raytracer::Color c(0.2, 0.3, 0.4);
    EXPECT_EQ(c * 2, raytracer::Color(0.4, 0.6, 0.8));
    EXPECT_EQ(2 * c, raytracer::Color(0.4, 0.6, 0.8));
}

// Multiplying colors
TEST_F(ColorTest, Multiplying_colors)
{
    raytracer::Color c1(1, 0.2, 0.4);
    raytracer::Color c2(0.9, 1, 0.1);
    EXPECT_EQ(c1 * c2, raytracer::Color(0.9, 0.2, 0.04));
}
