#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "matrix.hpp"
#include "utils.hpp"

namespace raytracer {
    class Ray;
    class Canvas;
    class World;

    class ProgressBar {
    public:
        virtual void tick() = 0;
    };

    class Camera {
    public:
        // Constructor for the Camera class
        Camera(int hsize, int vsize, double fieldOfView);

        // Method for computing the ray for a pixel
        Ray rayForPixel(int px, int py) const;

        // Method for rendering the scene
        Canvas render(const World &world, ProgressBar *pb = nullptr) const;

    public:
        const int hsize;          // The horizontal size of the image
        const int vsize;          // The vertical size of the image
        const double fieldOfView; // The field of view of the camera in radians

    private:
        const double halfView;   // Half the field of view in radians
        const double aspect;     // The aspect ratio of the image
        const double halfWidth;  // Half the width of the view plane in world units
        const double halfHeight; // Half the height of the view plane in world units

    public:
        const double pixelSize; // The size of each pixel in world units

    public:
        Matrix transform; // The transformation matrix of the camera
    };

} // namespace raytracer

#endif // __CAMERA_HPP__