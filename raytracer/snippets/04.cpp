#include "raytracer.hpp"

int main(void)
{
    // start the ray at z = -5
    raytracer::Tuple ray_origin = raytracer::Point(0, 0, -5);

    // put the wall at z = 10
    double wall_z = 10;

    // put the wall 7 units away from the origin
    double wall_size = 7.0;

    // the canvas is 1000 pixels wide and 1000 pixels high
    int canvas_pixels = 1000;

    // each pixel is 1 unit
    double pixel_size = wall_size / canvas_pixels;

    // half the width of the wall
    double half = wall_size / 2;

    // the canvas
    raytracer::Canvas c(canvas_pixels, canvas_pixels);
    raytracer::Color red(1, 0, 0);
    raytracer::Sphere s;
    s.material() = raytracer::Material();
    s.material().color() = raytracer::Color(0.2, 1, 0.3);

    raytracer::PointLight light(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));

#pragma omp parallel for
    // for each row of pixels in the canvas
    for (int y = 0; y < canvas_pixels; y++) {
        // the world y coordinate is the wall y coordinate
        double world_y = half - pixel_size * y;

        // for each pixel in the row
        for (int x = 0; x < canvas_pixels; x++) {
            // the world x coordinate is the wall x coordinate
            double world_x = -half + pixel_size * x;

            // describe the point on the wall that the ray will target
            raytracer::Tuple position = raytracer::Point(world_x, world_y, wall_z);

            // create a ray
            raytracer::Ray r(ray_origin, (position - ray_origin).normalize());

            // compute the intersections between the ray and the sphere
            raytracer::Intersections xs = s.intersect(r);

            // if the ray intersects the sphere, color the pixel red
            const raytracer::Intersection *i = xs.hit();
            if (i != nullptr) {
                raytracer::Point point = r.position(i->t()).asPoint();
                raytracer::Vector normal = i->shape().normalAt(point).asVector();
                raytracer::Vector eye = (-r.direction()).asVector();

                raytracer::Color color = i->shape().material().lighting(light, point, eye, normal);

                c.writePixel(x, y, color);
            }
        }
    }

    std::cout << c.toPPM() << std::endl;
}
