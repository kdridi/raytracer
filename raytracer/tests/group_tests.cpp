#include "raytracer.hpp"

#include <gmock/gmock.h>

class GroupTest : public ::testing::Test {};

// Creating a new group
TEST_F(GroupTest, Creating_a_new_group)
{
    raytracer::Group group;
    ASSERT_TRUE(group.transform() == raytracer::Matrix::identity(4));
    ASSERT_TRUE(group.empty());
}

// Adding a child to a group
TEST_F(GroupTest, Adding_a_child_to_a_group)
{
    raytracer::Group group;
    raytracer::Sphere *sphere = new raytracer::Sphere();
    group.add(sphere);
    ASSERT_TRUE(group.size() == 1);
    ASSERT_TRUE(&group[0] == sphere);
}

// Intersecting a ray with an empty group
TEST_F(GroupTest, Intersecting_a_ray_with_an_empty_group)
{
    raytracer::Group group;
    raytracer::Ray ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    auto intersections = group.intersect(ray);
    ASSERT_EQ(intersections.count(), 0);
}

// Intersecting a ray with a nonempty group
TEST_F(GroupTest, Intersecting_a_ray_with_a_nonempty_group)
{
    raytracer::Group group;
    raytracer::Sphere *s1 = new raytracer::Sphere();
    raytracer::Sphere *s2 = new raytracer::Sphere();
    raytracer::Sphere *s3 = new raytracer::Sphere();
    s2->transform() = raytracer::Matrix::translation(0, 0, -3);
    s3->transform() = raytracer::Matrix::translation(5, 0, 0);
    group.add(s1);
    group.add(s2);
    group.add(s3);
    raytracer::Ray ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    auto intersections = group.localIntersect(ray);
    ASSERT_EQ(intersections.count(), 4);
    ASSERT_EQ(&(intersections[0].shape()), s2);
    ASSERT_EQ(&(intersections[1].shape()), s2);
    ASSERT_EQ(&(intersections[2].shape()), s1);
    ASSERT_EQ(&(intersections[3].shape()), s1);
}

// Intersecting a transformed group
TEST_F(GroupTest, Intersecting_a_transformed_group)
{
    raytracer::Group group;
    group.transform() = raytracer::Matrix::scaling(2, 2, 2);
    raytracer::Sphere *s = new raytracer::Sphere();
    s->transform() = raytracer::Matrix::translation(5, 0, 0);
    group.add(s);
    raytracer::Ray ray(raytracer::Point(10, 0, -10), raytracer::Vector(0, 0, 1));
    auto intersections = group.intersect(ray);
    ASSERT_EQ(intersections.count(), 2);
}
