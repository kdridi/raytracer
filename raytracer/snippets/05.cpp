#include "raytracer.hpp"

int main()
{
    raytracer::World world;
    world.light() = new raytracer::PointLight(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));

    raytracer::Sphere *floor = new raytracer::Sphere();
    floor->transform() = raytracer::Matrix::scaling(10, 0.01, 10);
    floor->material() = raytracer::Material();
    floor->material().color() = raytracer::Color(1, 0.9, 0.9);
    floor->material().specular() = 0;
    world.shapes().push_back(floor);

    raytracer::Sphere *leftWall = new raytracer::Sphere();
    leftWall->transform() = raytracer::Matrix::translation(0, 0, 5) * raytracer::Matrix::rotationY(-M_PI / 4) * raytracer::Matrix::rotationX(M_PI / 2) * raytracer::Matrix::scaling(10, 0.01, 10);
    leftWall->material() = floor->material();
    world.shapes().push_back(leftWall);

    raytracer::Sphere *rightWall = new raytracer::Sphere();
    rightWall->transform() = raytracer::Matrix::translation(0, 0, 5) * raytracer::Matrix::rotationY(M_PI / 4) * raytracer::Matrix::rotationX(M_PI / 2) * raytracer::Matrix::scaling(10, 0.01, 10);
    rightWall->material() = floor->material();
    world.shapes().push_back(rightWall);

    raytracer::Sphere *middle = new raytracer::Sphere();
    middle->transform() = raytracer::Matrix::translation(-0.5, 1, 0.5);
    middle->material() = raytracer::Material();
    middle->material().color() = raytracer::Color(0.1, 1, 0.5);
    middle->material().diffuse() = 0.7;
    middle->material().specular() = 0.3;
    world.shapes().push_back(middle);

    raytracer::Sphere *right = new raytracer::Sphere();
    right->transform() = raytracer::Matrix::translation(1.5, 0.5, -0.5) * raytracer::Matrix::scaling(0.5, 0.5, 0.5);
    right->material() = raytracer::Material();
    right->material().color() = raytracer::Color(0.5, 1, 0.1);
    right->material().diffuse() = 0.7;
    right->material().specular() = 0.3;
    world.shapes().push_back(right);

    raytracer::Sphere *left = new raytracer::Sphere();
    left->transform() = raytracer::Matrix::translation(-1.5, 0.33, -0.75) * raytracer::Matrix::scaling(0.33, 0.33, 0.33);
    left->material() = raytracer::Material();
    left->material().color() = raytracer::Color(1, 0.8, 0.1);
    left->material().diffuse() = 0.7;
    left->material().specular() = 0.3;
    world.shapes().push_back(left);

    raytracer::Camera camera(1024, 1024, M_PI / 3);
    camera.transform = raytracer::Matrix::viewTransform(raytracer::Point(0, 1.5, -5), raytracer::Point(0, 1, 0), raytracer::Vector(0, 1, 0));

    raytracer::Canvas canvas = camera.render(world);

    std::cout << canvas.toPPM();

    return 0;
}
