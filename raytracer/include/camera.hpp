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
        Camera(int hsize, int vsize, double fieldOfView);

        Ray rayForPixel(int px, int py) const;
        Canvas render(const World &world, ProgressBar *pb = nullptr) const;

    public:
        int hsize;
        int vsize;
        double fieldOfView;
        Matrix transform;
        double pixelSize;
        double halfWidth;
        double halfHeight;
    };

} // namespace raytracer

#endif // __CAMERA_HPP__