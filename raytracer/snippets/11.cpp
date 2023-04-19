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

    raytracer::Shape *hexagone = raytracer::Group::Hexagon();
    hexagone->transform() = raytracer::Matrix::translation(0.0, 0.5, 0.0) * raytracer::Matrix::scaling(2.0, 2.0, 2.0);
    hexagone->material() = raytracer::Material();
    hexagone->material().color() = raytracer::Color(1, 0.8, 0.1);
    hexagone->material().diffuse() = 0.7;
    hexagone->material().specular() = 0.3;
    world.shapes().push_back(hexagone);

    raytracer::Camera camera(512, 512, M_PI / 3);
    camera.transform = raytracer::Matrix::viewTransform(raytracer::Point(0, 10.0, -10.0), raytracer::Point(0, 0, 0), raytracer::Vector(0, 1, 0));

    raytracer::Canvas canvas = camera.render(world);

    std::cout << canvas.toPPM();

    return 0;
}
