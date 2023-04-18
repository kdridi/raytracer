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

// Lighting with the eye between light and surface, eye offset 45 degrees
TEST_F(DefaultMaterialTest, Lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees)
{
    raytracer::PointLight light(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, std::sqrt(2) / 2, -std::sqrt(2) / 2);
    raytracer::Vector normalv(0, 0, -1);
    raytracer::Color result = m.lighting(light, position, eyev, normalv);
    EXPECT_TRUE(result == raytracer::Color(1.0, 1.0, 1.0));
}

// Lighting with eye opposite surface, light offset 45 degrees
TEST_F(DefaultMaterialTest, Lighting_with_eye_opposite_surface_light_offset_45_degrees)
{
    raytracer::PointLight light(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, 0, -1);
    raytracer::Vector normalv(0, 0, -1);
    raytracer::Color result = m.lighting(light, position, eyev, normalv);
    EXPECT_TRUE(result == raytracer::Color(0.7364, 0.7364, 0.7364));
}

// Lighting with eye in the path of the reflection vector
TEST_F(DefaultMaterialTest, Lighting_with_eye_in_the_path_of_the_reflection_vector)
{
    raytracer::PointLight light(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, -std::sqrt(2) / 2, -std::sqrt(2) / 2);
    raytracer::Vector normalv(0, 0, -1);
    raytracer::Color result = m.lighting(light, position, eyev, normalv);
    EXPECT_TRUE(result == raytracer::Color(1.6364, 1.6364, 1.6364));
}

// Lighting with the light behind the surface
TEST_F(DefaultMaterialTest, Lighting_with_the_light_behind_the_surface)
{
    raytracer::PointLight light(raytracer::Point(0, 0, 10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, 0, -1);
    raytracer::Vector normalv(0, 0, -1);
    raytracer::Color result = m.lighting(light, position, eyev, normalv);
    EXPECT_TRUE(result == raytracer::Color(0.1, 0.1, 0.1));
}

// Lighting with the surface in shadow
TEST_F(DefaultMaterialTest, Lighting_with_the_surface_in_shadow)
{
    raytracer::PointLight light(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    raytracer::Vector eyev(0, 0, -1);
    raytracer::Vector normalv(0, 0, -1);
    bool inShadow = true;
    raytracer::Color result = m.lighting(light, position, eyev, normalv, inShadow);
    EXPECT_TRUE(result == raytracer::Color(0.1, 0.1, 0.1));
}
