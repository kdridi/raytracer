#include "raytracer.hpp"

using namespace raytracer;

int main()
{
    Canvas c(500, 500);
    int offset = 50;
    Matrix r = Matrix::rotationZ(M_PI / 6);
    Tuple p = Tuple::point(0, 1, 0);
    for (int i = 0; i < 12; i++) {
        int px = std::floor(map_range(p.x, -1, 1, 50, c.width() - 50));
        int py = std::floor(map_range(p.y, -1, 1, 50, c.height() - 50));
        c.drawCircle(px, py, 20, Color::Green());
        p = r * p;
    }
    std::cout << c.toPPM() << std::endl;
}
