#include "camera.hpp"
#include "canvas.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include "world.hpp"

// #include <progressbar/progressbar.h>

using namespace raytracer;

Camera::Camera(int hsize, int vsize, double fieldOfView)
    : hsize(hsize), vsize(vsize), fieldOfView(fieldOfView), transform(Matrix::identity(4)), pixelSize(0), halfWidth(0), halfHeight(0)
{
    double halfView = std::tan(fieldOfView / 2);
    double aspect = static_cast<double>(hsize) / static_cast<double>(vsize);
    if (aspect >= 1) {
        halfWidth = halfView;
        halfHeight = halfView / aspect;
    } else {
        halfWidth = halfView * aspect;
        halfHeight = halfView;
    }
    pixelSize = (halfWidth * 2) / hsize;
}

Ray Camera::rayForPixel(int px, int py) const
{
    double xOffset = (px + 0.5) * pixelSize;
    double yOffset = (py + 0.5) * pixelSize;
    double xWorld = halfWidth - xOffset;
    double yWorld = halfHeight - yOffset;
    Tuple pixel = transform.inverse() * Point(xWorld, yWorld, -1);
    Tuple origin = transform.inverse() * Point(0, 0, 0);
    Vector direction = (pixel - origin).normalize().asVector();
    return Ray(origin, direction);
}

Canvas Camera::render(const World &world, ProgressBar *pb) const
{
    Canvas image(hsize, vsize);

#pragma omp parallel for
    for (int y = 0; y < vsize; y++) {
#pragma omp parallel for
        for (int x = 0; x < hsize; x++) {
            Ray r = rayForPixel(x, y);
            Color c = world.colorAt(r);
            image.writePixel(x, y, c);
            if (pb)
                pb->tick();
        }
    }

    return image;
}
