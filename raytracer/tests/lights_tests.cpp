#include "raytracer.hpp"

#include <cmath>
#include <gmock/gmock.h>

class LightsTest : public testing::Test {};

// A point light has a position and intensity
TEST_F(LightsTest, A_point_light_has_a_position_and_intensity)
{
    raytracer::PointLight light(raytracer::Point(0, 0, 0), raytracer::Color(1, 1, 1));
    EXPECT_TRUE(light.position() == raytracer::Point(0, 0, 0));
    EXPECT_TRUE(light.intensity() == raytracer::Color(1, 1, 1));
}
