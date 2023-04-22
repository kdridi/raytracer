#include "raytracer.hpp"

#include <iomanip>

class ProgressBar : public raytracer::ProgressBar {
public:
    ProgressBar(std::string const &message, size_t total)
        : m_start(std::chrono::system_clock::now()), m_mutex(), m_message(message), m_total(total), m_current(0)
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    ~ProgressBar()
    {
        pthread_mutex_destroy(&m_mutex);
        std::cout << std::endl;
    }

    void tick() override
    {
        m_current += 1;
        double percent = (double)(m_current) / (double)m_total;
        size_t max = (size_t)(50 * percent);
        auto current_time = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - m_start).count();
        auto remaining = (size_t)((elapsed / percent - elapsed) / 1000000000.0);
        auto sec = remaining % 60;
        auto min = (remaining / 60) % 60;
        auto hour = remaining / 3600;

        pthread_mutex_lock(&m_mutex);
        std::cout << m_message << " [";
        size_t i = 0;
        for (; i < max; ++i)
            std::cout << "=";
        for (; i < 50; ++i)
            std::cout << " ";
        std::cout << "] " << std::setfill(' ') << std::setw(3) << (int)(100.0 * percent) << "%"
                  << " " << std::setfill('0') << std::setw(2) << hour << "h " << std::setw(2) << min << "m " << std::setw(2) << sec << "s                   \r"
                  << std::flush;
        pthread_mutex_unlock(&m_mutex);
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    pthread_mutex_t m_mutex;
    std::string m_message;
    size_t m_total;
    size_t m_current;
};

int main()
{
    raytracer::World world;
    world.light() = new raytracer::PointLight(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1));

    raytracer::Shape *floor = new raytracer::Plane();
    floor->material() = raytracer::Material();
    floor->material().color() = raytracer::Color(1, 0.9, 0.9);
    floor->material().specular() = 0;
    floor->material().pattern = new raytracer::RingPattern(raytracer::Color::Red(), raytracer::Color::White());
    world.shapes().push_back(floor);

    std::vector<raytracer::Shape *> shapes;
    raytracer::OBJFileParser parser = raytracer::OBJFileParser::ParseFile("teapot.obj");
    for (auto &face : parser.faces) {
        face.material() = raytracer::Material();
        face.material().color() = raytracer::Color(0.1, 1, 0.5);
        face.material().diffuse() = 0.7;
        face.material().specular() = 0.3;
        // face.material().pattern = new raytracer::PerlinPattern(raytracer::Color::Green(), raytracer::Color::Blue());
        // face.material().pattern->transform = raytracer::Matrix::scaling(0.25, 0.25, 0.25);
        raytracer::Triangle *triangle = new raytracer::Triangle(face);
        shapes.push_back(triangle);
    }
    raytracer::Shape *teapot = new raytracer::KDTree(shapes, 8);
    world.shapes().push_back(teapot);

    raytracer::Camera camera(32, 32, M_PI / 3);
    camera.transform = raytracer::Matrix::viewTransform(raytracer::Point(0, 3.0, -5.0), raytracer::Point(0, 0, 0), raytracer::Vector(0, 1, 0));

    ProgressBar progressbar("Rendering", camera.hsize * camera.vsize);
    raytracer::Canvas canvas = camera.render(world, &progressbar);

    canvas.savePPM("12.ppm");

    return 0;
}
