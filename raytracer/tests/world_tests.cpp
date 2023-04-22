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

    raytracer::World *w = raytracer::World::Default();

    EXPECT_TRUE(*w->light() == light);

    bool s1_found = false;
    bool s2_found = false;

    for (raytracer::Shape *shape : w->shapes()) {
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

    delete w;
}

// Intersect a world with a ray
TEST_F(WorldTest, Intersect_a_world_with_a_ray)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    auto xs = w->intersect(r);
    EXPECT_EQ(xs.count(), 4);
    EXPECT_EQ(xs[0].t(), 4.0);
    EXPECT_EQ(xs[1].t(), 4.5);
    EXPECT_EQ(xs[2].t(), 5.5);
    EXPECT_EQ(xs[3].t(), 6.0);
    delete w;
}

// Shading an intersection
TEST_F(WorldTest, Shading_an_intersection)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersection i(4, *w->shapes()[0]);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w->shadeHit(comps);
    EXPECT_TRUE(c == raytracer::Color(0.38066, 0.47583, 0.2855));
    delete w;
}

// Shading an intersection from the inside
TEST_F(WorldTest, Shading_an_intersection_from_the_inside)
{
    raytracer::World *w = raytracer::World::Default();
    delete w->light();
    w->light() = new raytracer::PointLight(raytracer::Point(0, 0.25, 0), raytracer::Color(1, 1, 1));
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    raytracer::Shape &s = *w->shapes()[1];
    raytracer::Intersections xs = {raytracer::Intersection(0.5, s)};
    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    raytracer::Color c = w->shadeHit(comps);
    EXPECT_TRUE(c == raytracer::Color(0.90498, 0.90498, 0.90498));
    delete w;
}

// The color when a ray misses
TEST_F(WorldTest, The_color_when_a_ray_misses)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 1, 0));
    raytracer::Color c = w->colorAt(r);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
}

// The color when a ray hits
TEST_F(WorldTest, The_color_when_a_ray_hits)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Color c = w->colorAt(r);
    EXPECT_TRUE(c == raytracer::Color(0.38066, 0.47583, 0.2855));
    delete w;
}

// The color with an intersection behind the ray
TEST_F(WorldTest, The_color_with_an_intersection_behind_the_ray)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Sphere *outer = dynamic_cast<raytracer::Sphere *>(w->shapes()[0]);
    outer->material().ambient() = 1;
    raytracer::Sphere *inner = dynamic_cast<raytracer::Sphere *>(w->shapes()[1]);
    inner->material().ambient() = 1;
    raytracer::Ray r(raytracer::Point(0, 0, 0.75), raytracer::Vector(0, 0, -1));
    raytracer::Color c = w->colorAt(r);
    EXPECT_TRUE(c == inner->material().color());
    delete w;
}

// There is no shadow when nothing is collinear with point and light
TEST_F(WorldTest, There_is_no_shadow_when_nothing_is_collinear_with_point_and_light)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Point p(0, 10, 0);
    EXPECT_FALSE(w->isShadowed(p));
    delete w;
}

// The shadow when an object is between the point and the light
TEST_F(WorldTest, The_shadow_when_an_object_is_between_the_point_and_the_light)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Point p(10, -10, 10);
    EXPECT_TRUE(w->isShadowed(p));
    delete w;
}

// There is no shadow when an object is behind the light
TEST_F(WorldTest, There_is_no_shadow_when_an_object_is_behind_the_light)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Point p(-20, 20, -20);
    EXPECT_FALSE(w->isShadowed(p));
    delete w;
}

// There is no shadow when an object is behind the point
TEST_F(WorldTest, There_is_no_shadow_when_an_object_is_behind_the_point)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Point p(-2, 2, -2);
    EXPECT_FALSE(w->isShadowed(p));
    delete w;
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
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w.shadeHit(comps);
    EXPECT_TRUE(c == raytracer::Color(0.1, 0.1, 0.1));
}

// The reflected color for a nonreflective material
TEST_F(WorldTest, The_reflected_color_for_a_nonreflective_material)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    raytracer::Shape *s = w->shapes()[1];
    s->material().ambient() = 1;
    raytracer::Intersection i(1, *s);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w->reflectedColor(comps);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
}

// The reflected color for a reflective material
TEST_F(WorldTest, The_reflected_color_for_a_reflective_material)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Plane *p = new raytracer::Plane();
    p->material().reflective = 0.5;
    p->transform() = raytracer::Matrix::translation(0, -1, 0);
    w->shapes().push_back(p);
    raytracer::Ray r(raytracer::Point(0, 0, -3), raytracer::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    raytracer::Intersection i(sqrt(2), *p);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w->reflectedColor(comps);
    EXPECT_TRUE(c == raytracer::Color(0.19032, 0.2379, 0.14274));
    delete w;
}

// shadeHit is given an intersection in shadow
TEST_F(WorldTest, shadeHit_is_given_an_intersection_in_shadow)
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
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w.shadeHit(comps);
    EXPECT_TRUE(c == raytracer::Color(0.1, 0.1, 0.1));
}

// colorAt with mutually reflective surfaces
TEST_F(WorldTest, colorAt_with_mutually_reflective_surfaces)
{
    raytracer::World w;
    w.light() = new raytracer::PointLight(raytracer::Point(0, 0, 0), raytracer::Color(1, 1, 1));

    raytracer::Plane *lower = new raytracer::Plane();
    lower->material().reflective = 1;
    lower->transform() = raytracer::Matrix::translation(0, -1, 0);
    w.shapes().push_back(lower);

    raytracer::Plane *upper = new raytracer::Plane();
    upper->material().reflective = 1;
    upper->transform() = raytracer::Matrix::translation(0, 1, 0);
    w.shapes().push_back(upper);

    raytracer::Ray r(raytracer::Point(0, 0, 0), raytracer::Vector(0, 1, 0));
    EXPECT_NO_THROW(w.colorAt(r));
}

// the reflected color at the maximum recursive depth
TEST_F(WorldTest, the_reflected_color_at_the_maximum_recursive_depth)
{
    raytracer::World *w = raytracer::World::Default();

    raytracer::Plane *p = new raytracer::Plane();
    p->material().reflective = 0.5;
    p->transform() = raytracer::Matrix::translation(0, -1, 0);
    w->shapes().push_back(p);

    raytracer::Ray r(raytracer::Point(0, 0, -3), raytracer::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    raytracer::Intersection i(sqrt(2), *p);
    raytracer::Computations comps = i.prepareComputations(r, raytracer::Intersections{i});
    raytracer::Color c = w->reflectedColor(comps, 0);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
}

// The refracted color with an opaque surface
TEST_F(WorldTest, The_refracted_color_with_an_opaque_surface)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Shape &s = *w->shapes()[0];
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = {raytracer::Intersection(4, s), raytracer::Intersection(6, s)};
    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    raytracer::Color c = w->refractedColor(comps, 0);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
}

// The refracted color at the maximum recursive depth
TEST_F(WorldTest, The_refracted_color_at_the_maximum_recursive_depth)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Shape &s = *w->shapes()[0];
    s.material().transparency = 1.0;
    s.material().refractiveIndex = 1.5;
    raytracer::Ray r(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    raytracer::Intersections xs = {raytracer::Intersection(4, s), raytracer::Intersection(6, s)};
    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    raytracer::Color c = w->refractedColor(comps, 0);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
}

// The refracted color under total internal reflection
TEST_F(WorldTest, The_refracted_color_under_total_internal_reflection)
{
    raytracer::World *w = raytracer::World::Default();
    raytracer::Shape &s = *w->shapes()[0];
    s.material().transparency = 1.0;
    s.material().refractiveIndex = 1.5;
    raytracer::Ray r(raytracer::Point(0, 0, sqrt(2) / 2), raytracer::Vector(0, 1, 0));
    raytracer::Intersections xs = {
        raytracer::Intersection(-sqrt(2) / 2, s),
        raytracer::Intersection(sqrt(2) / 2, s)};
    raytracer::Computations comps = xs[1].prepareComputations(r, xs);
    raytracer::Color c = w->refractedColor(comps, 5);
    EXPECT_TRUE(c == raytracer::Color(0, 0, 0));
    delete w;
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

// The refracted color with a refracted ray
TEST_F(WorldTest, The_refracted_color_with_a_refracted_ray)
{
    raytracer::World *w = raytracer::World::Default();

    raytracer::Shape &A = *w->shapes()[0];
    A.material().ambient() = 1.0;
    A.material().pattern = new TestPattern();

    raytracer::Shape &B = *w->shapes()[1];
    B.material().transparency = 1.0;
    B.material().refractiveIndex = 1.5;

    raytracer::Ray r(raytracer::Point(0, 0, 0.1), raytracer::Vector(0, 1, 0));
    raytracer::Intersections xs = {
        raytracer::Intersection(-0.9899, A),
        raytracer::Intersection(-0.4899, B),
        raytracer::Intersection(0.4899, B),
        raytracer::Intersection(0.9899, A)};

    raytracer::Computations comps = xs[2].prepareComputations(r, xs);
    raytracer::Color c = w->refractedColor(comps, 5);

    EXPECT_TRUE(c == raytracer::Color(0, 0.99888, 0.04725));
    delete w;
}

// shade_hit() with a transparent material
TEST_F(WorldTest, ShadeHit_with_a_transparent_material)
{
    raytracer::World *w = raytracer::World::Default();

    raytracer::Plane *floor = new raytracer::Plane();
    floor->transform() = raytracer::Matrix::translation(0, -1, 0);
    floor->material().transparency = 0.5;
    floor->material().refractiveIndex = 1.5;
    w->shapes().push_back(floor);

    raytracer::Sphere *ball = new raytracer::Sphere();
    ball->material().color() = raytracer::Color(1, 0, 0);
    ball->material().ambient() = 0.5;
    ball->transform() = raytracer::Matrix::translation(0, -3.5, -0.5);
    w->shapes().push_back(ball);

    raytracer::Ray r(raytracer::Point(0, 0, -3), raytracer::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    raytracer::Intersections xs = {
        raytracer::Intersection(sqrt(2), *floor)};

    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    raytracer::Color c = w->shadeHit(comps, 5);

    EXPECT_TRUE(c == raytracer::Color(0.93642, 0.68642, 0.68642));
    delete w;
}

// shade_hit() with a reflective, transparent materia
TEST_F(WorldTest, ShadeHit_with_a_reflective_transparent_materia)
{
    raytracer::World *w = raytracer::World::Default();

    raytracer::Ray r(raytracer::Point(0, 0, -3), raytracer::Vector(0, -sqrt(2) / 2, sqrt(2) / 2));

    raytracer::Plane *floor = new raytracer::Plane();
    floor->transform() = raytracer::Matrix::translation(0, -1, 0);
    floor->material().reflective = 0.5;
    floor->material().transparency = 0.5;
    floor->material().refractiveIndex = 1.5;
    w->shapes().push_back(floor);

    raytracer::Sphere *ball = new raytracer::Sphere();
    ball->material().color() = raytracer::Color(1, 0, 0);
    ball->material().ambient() = 0.5;
    ball->transform() = raytracer::Matrix::translation(0, -3.5, -0.5);
    w->shapes().push_back(ball);

    raytracer::Intersections xs = {
        raytracer::Intersection(sqrt(2), *floor)};

    raytracer::Computations comps = xs[0].prepareComputations(r, xs);
    raytracer::Color c = w->shadeHit(comps, 5);

    EXPECT_TRUE(c == raytracer::Color(0.93391, 0.69643, 0.69243));
    delete w;
}
