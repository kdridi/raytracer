#include "raytracer.hpp"

#include <gmock/gmock.h>

class CameraTest : public testing::Test {};

// Constructing a camera
TEST_F(CameraTest, Constructing_a_camera)
{
    int hsize = 160;
    int vsize = 120;
    double fieldOfView = M_PI / 2;
    raytracer::Camera c(hsize, vsize, fieldOfView);
    EXPECT_EQ(c.hsize, hsize);
    EXPECT_EQ(c.vsize, vsize);
    EXPECT_EQ(c.fieldOfView, fieldOfView);
    EXPECT_TRUE(c.transform == raytracer::Matrix::identity(4));
}

// The pixel size for a horizontal canvas
TEST_F(CameraTest, The_pixel_size_for_a_horizontal_canvas)
{
    raytracer::Camera c(200, 125, M_PI / 2);
    EXPECT_TRUE(double_equals(c.pixelSize, 0.01));
}

// The pixel size for a vertical canvas
TEST_F(CameraTest, The_pixel_size_for_a_vertical_canvas)
{
    raytracer::Camera c(125, 200, M_PI / 2);
    EXPECT_TRUE(double_equals(c.pixelSize, 0.01));
}

// Constructing a ray through the center of the canvas
TEST_F(CameraTest, Constructing_a_ray_through_the_center_of_the_canvas)
{
    raytracer::Camera c(201, 101, M_PI / 2);
    raytracer::Ray r = c.rayForPixel(100, 50);
    EXPECT_TRUE(r.origin() == raytracer::Point(0, 0, 0));
    EXPECT_TRUE(r.direction() == raytracer::Vector(0, 0, -1));
}

// Constructing a ray through a corner of the canvas
TEST_F(CameraTest, Constructing_a_ray_through_a_corner_of_the_canvas)
{
    raytracer::Camera c(201, 101, M_PI / 2);
    raytracer::Ray r = c.rayForPixel(0, 0);
    EXPECT_TRUE(r.origin() == raytracer::Point(0, 0, 0));
    EXPECT_TRUE(r.direction() == raytracer::Vector(0.66519, 0.33259, -0.66851));
}

// Constructing a ray when the camera is transformed
TEST_F(CameraTest, Constructing_a_ray_when_the_camera_is_transformed)
{
    raytracer::Camera c(201, 101, M_PI / 2);
    c.transform = raytracer::Matrix::rotationY(M_PI / 4) * raytracer::Matrix::translation(0, -2, 5);
    raytracer::Ray r = c.rayForPixel(100, 50);
    EXPECT_TRUE(r.origin() == raytracer::Point(0, 2, -5));
    EXPECT_TRUE(r.direction() == raytracer::Vector(std::sqrt(2) / 2, 0, -std::sqrt(2) / 2));
}

// Rendering a world with a camera
TEST_F(CameraTest, Rendering_a_world_with_a_camera)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Camera c(11, 11, M_PI / 2);
    raytracer::Point from(0, 0, -5);
    raytracer::Point to(0, 0, 0);
    raytracer::Vector up(0, 1, 0);
    c.transform = raytracer::Matrix::viewTransform(from, to, up);
    raytracer::Canvas image = c.render(*w);
    EXPECT_TRUE(image.pixelAt(5, 5) == raytracer::Color(0.38066, 0.47583, 0.2855));
    delete w;
}
