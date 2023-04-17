#include "raytracer.hpp"

#include <cmath>
#include <gmock/gmock.h>

class MaterialTest : public testing::Test {};

// The default material
TEST_F(MaterialTest, The_default_material)
{
    raytracer::Material m;
    EXPECT_TRUE(m.color() == raytracer::Color(1, 1, 1));
    EXPECT_EQ(m.ambient(), 0.1);
    EXPECT_EQ(m.diffuse(), 0.9);
    EXPECT_EQ(m.specular(), 0.9);
    EXPECT_EQ(m.shininess(), 200.0);
}

class DefaultMaterialTest : public testing::Test {
protected:
    raytracer::Material m;
    raytracer::Point position;

    DefaultMaterialTest() : m(), position(0, 0, 0)
    {
    }

    void SetUp() override
    {
        m = raytracer::Material();
        position = raytracer::Point(0, 0, 0);
    }
};

// Lighting with the eye between the light and the surface
TEST_F(DefaultMaterialTest, Lighting_with_the_eye_between_the_light_and_the_surface)
{
    raytracer::PointLight light(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, 0, -1);
    raytracer::Vector normalv(0, 0, -1);
    raytracer::Color result = m.lighting(light, position, eyev, normalv);
    EXPECT_TRUE(result == raytracer::Color(1.9, 1.9, 1.9));
}
