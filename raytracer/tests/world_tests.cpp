#include "raytracer.hpp"

#include <gmock/gmock.h>

class WorldTest : public testing::Test {};

// Creating a world
TEST_F(WorldTest, Creating_a_world)
{
    raytracer::World w;
    EXPECT_TRUE(w.shapes().empty());
    EXPECT_TRUE(w.light() == nullptr);
}

// The default world
TEST_F(WorldTest, The_default_world)
{
    raytracer::PointLight light(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));

    raytracer::Sphere s1;
    s1.material().color() = raytracer::Color(0.8, 1.0, 0.6);
    s1.material().diffuse() = 0.7;
    s1.material().specular() = 0.2;

    raytracer::Sphere s2;
    s2.transform() = raytracer::Matrix::scaling(0.5, 0.5, 0.5);

    raytracer::World w = raytracer::World::Default();

    EXPECT_TRUE(*w.light() == light);

    bool s1_found = false;
    bool s2_found = false;

    for (raytracer::Shape *shape : w.shapes()) {
        raytracer::Sphere *s = dynamic_cast<raytracer::Sphere *>(shape);

        if (*s == s1) {
            s1_found = true;
            break;
        }

        if (*s == s2) {
            s2_found = true;
            break;
        }
    }
}

// Intersect a world with a ray
TEST_F(WorldTest, Intersect_a_world_with_a_ray)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    auto xs = w.intersect(r);
    EXPECT_EQ(xs.count(), 4);
    EXPECT_EQ(xs[0].t(), 4.0);
    EXPECT_EQ(xs[1].t(), 4.5);
    EXPECT_EQ(xs[2].t(), 5.5);
    EXPECT_EQ(xs[3].t(), 6.0);
}

// Shading an intersection
TEST_F(WorldTest, Shading_an_intersection)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersection i(4, *w.shapes()[0]);
    raytracer::Computations comps = i.prepareComputations(r);
    raytracer::Color c = w.shadeHit(comps, i.shape());
    EXPECT_TRUE(c == raytracer::Color(0.38066, 0.47583, 0.2855));
}

// Shading an intersection from the inside
// TEST_F(WorldTest, Shading_an_intersection_from_the_inside)
// {
//     raytracer::World w = raytracer::World::Default();
//     w.light() = new raytracer::PointLight(raytracer::Point(0, 0.25, 0), raytracer::Color(1, 1, 1));
//     raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
//     raytracer::Shape *s = w.shapes()[1];
//     raytracer::Intersection i(0.5, *s);
//     raytracer::Computations comps = i.prepareComputations(r);
//     raytracer::Color c = w.shadeHit(comps, i.shape());
//     std::cout << "color: " << c << std::endl;
//     EXPECT_TRUE(c == raytracer::Color(0.90498, 0.90498, 0.90498));
// }

// The color when a ray misses
TEST_F(WorldTest, The_color_when_a_ray_misses)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 1, 0));
    raytracer::Color c = w.colorAt(r);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
}

// The color when a ray hits
TEST_F(WorldTest, The_color_when_a_ray_hits)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Color c = w.colorAt(r);
    EXPECT_TRUE(c == raytracer::Color(0.38066, 0.47583, 0.2855));
}

// The color with an intersection behind the ray
TEST_F(WorldTest, The_color_with_an_intersection_behind_the_ray)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Sphere *outer = dynamic_cast<raytracer::Sphere *>(w.shapes()[0]);
    outer->material().ambient() = 1;
    raytracer::Sphere *inner = dynamic_cast<raytracer::Sphere *>(w.shapes()[1]);
    inner->material().ambient() = 1;
    raytracer::Ray r(raytracer::Point(0, 0, 0.75), raytracer::Vector(0, 0, -1));
    raytracer::Color c = w.colorAt(r);
    EXPECT_TRUE(c == inner->material().color());
}

// There is no shadow when nothing is collinear with point and light
TEST_F(WorldTest, There_is_no_shadow_when_nothing_is_collinear_with_point_and_light)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Point p(0, 10, 0);
    EXPECT_FALSE(w.isShadowed(p));
}

// The shadow when an object is between the point and the light
TEST_F(WorldTest, The_shadow_when_an_object_is_between_the_point_and_the_light)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Point p(10, -10, 10);
    EXPECT_TRUE(w.isShadowed(p));
}

// There is no shadow when an object is behind the light
TEST_F(WorldTest, There_is_no_shadow_when_an_object_is_behind_the_light)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Point p(-20, 20, -20);
    EXPECT_FALSE(w.isShadowed(p));
}

// There is no shadow when an object is behind the point
TEST_F(WorldTest, There_is_no_shadow_when_an_object_is_behind_the_point)
{
    raytracer::World w = raytracer::World::Default();
    raytracer::Point p(-2, 2, -2);
    EXPECT_FALSE(w.isShadowed(p));
}

// ShadeHit is given an intersection in shadow
TEST_F(WorldTest, ShadeHit_is_given_an_intersection_in_shadow)
{
    raytracer::World w;
    w.light() = new raytracer::PointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    raytracer::Sphere *s1 = new raytracer::Sphere();
    raytracer::Sphere *s2 = new raytracer::Sphere();
    s2->transform() = raytracer::Matrix::translation(0, 0, 10);
    w.shapes().push_back(s1);
    w.shapes().push_back(s2);
    raytracer::Ray r(raytracer::Point(0, 0, 5), raytracer::Vector(0, 0, 1));
    raytracer::Intersection i(4, *s2);
    raytracer::Computations comps = i.prepareComputations(r);
    raytracer::Color c = w.shadeHit(comps, i.shape());
    EXPECT_TRUE(c == raytracer::Color(0.1, 0.1, 0.1));
}
