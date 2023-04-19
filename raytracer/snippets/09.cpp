#include "raytracer.hpp"

int main()
{
    raytracer::World world;
    world.light() = new raytracer::PointLight(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));

    raytracer::Shape *floor = new raytracer::Plane();
    floor->material() = raytracer::Material();
    floor->material().color() = raytracer::Color(1, 0.9, 0.9);
    floor->material().specular() = 0;
    floor->material().pattern = new raytracer::RingPattern(raytracer::Color::Red(), raytracer::Color::White());
    // floor->material().pattern->transform = raytracer::Matrix::scaling(1, 0, 1);
    world.shapes().push_back(floor);

    raytracer::Sphere *middle = new raytracer::Sphere();
    middle->transform() = raytracer::Matrix::translation(-0.5, 1, 0.5);
    middle->material() = raytracer::Material();
    middle->material().color() = raytracer::Color(0.1, 1, 0.5);
    middle->material().diffuse() = 0.7;
    middle->material().specular() = 0.3;
    middle->material().pattern = new raytracer::PerlinPattern(raytracer::Color::Green(), raytracer::Color::Blue());
    middle->material().pattern->transform = raytracer::Matrix::scaling(0.25, 0.25, 0.25);
    world.shapes().push_back(middle);

    raytracer::Sphere *right = new raytracer::GlassSphere();
    right->transform() = raytracer::Matrix::translation(1.5, 0.5, -0.5) * raytracer::Matrix::scaling(0.5, 0.5, 0.5);
    world.shapes().push_back(right);

    raytracer::Sphere *left = new raytracer::Sphere();
    left->transform() = raytracer::Matrix::translation(-1.5, 0.33, -0.75) * raytracer::Matrix::scaling(0.33, 0.33, 0.33);
    left->material() = raytracer::Material();
    left->material().color() = raytracer::Color(1, 0.8, 0.1);
    left->material().diffuse() = 0.7;
    left->material().specular() = 0.3;
    world.shapes().push_back(left);

    raytracer::Cube *cube = new raytracer::Cube();
    cube->transform() = raytracer::Matrix::translation(0, 0.5, -1.5) * raytracer::Matrix::scaling(0.5, 0.5, 0.5);
    cube->material() = raytracer::Material();
    cube->material().color() = raytracer::Color(1, 0.8, 0.1);
    cube->material().diffuse() = 0.7;
    cube->material().specular() = 0.3;
    world.shapes().push_back(cube);

    raytracer::Camera camera(1024, 1024, M_PI / 3);
    camera.transform = raytracer::Matrix::viewTransform(raytracer::Point(0, 1.5, -5), raytracer::Point(0, 1, 0), raytracer::Vector(0, 1, 0));

    raytracer::Canvas canvas = camera.render(world);

    std::cout << canvas.toPPM();

    return 0;
}