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
            if (xs.hit()) {
                c.writePixel(x, y, red);
            }
        }
    }

    std::cout << c.toPPM() << std::endl;
}
