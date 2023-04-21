#include "camera.hpp"
#include "canvas.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"
#include "world.hpp"

// #include <progressbar/progressbar.h>

using namespace raytracer;

Camera::Camera(int hsize, int vsize, double fieldOfView)
    : hsize(hsize), vsize(vsize), fieldOfView(fieldOfView), halfView(std::tan(fieldOfView / 2)), aspect(static_cast<double>(hsize) / static_cast<double>(vsize)), halfWidth(aspect >= 1 ? halfView : halfView * aspect), halfHeight(aspect >= 1 ? halfView / aspect : halfView), pixelSize((halfWidth * 2) / hsize), transform(Matrix::identity(4))

{
}

Ray Camera::rayForPixel(int px, int py) const
{
    if (px < 0 || px >= hsize || py < 0 || py >= vsize)
        throw std::out_of_range("Pixel coordinates out of bounds.");

    const double xOffset = (px + 0.5) * pixelSize;
    const double yOffset = (py + 0.5) * pixelSize;
    const double xWorld = halfWidth - xOffset;
    const double yWorld = halfHeight - yOffset;
    const Tuple pixel = transform.inverse() * Point(xWorld, yWorld, -1);
    const Tuple origin = transform.inverse() * Point(0, 0, 0);
    const Vector direction = (pixel - origin).normalize().asVector();
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
