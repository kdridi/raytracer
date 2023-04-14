#include "raytracer.hpp"

using namespace raytracer;

class Projectile {
public:
    Projectile(const Tuple &position, const Tuple &velocity)
        : m_position(position), m_velocity(velocity)
    {
    }

    const Tuple &position() const
    {
        return m_position;
    }

    const Tuple &velocity() const
    {
        return m_velocity;
    }

private:
    Tuple m_position;
    Tuple m_velocity;
};

class Environment {
public:
    Environment(const Tuple &gravity, const Tuple &wind)
        : m_gravity(gravity), m_wind(wind)
    {
    }

    Projectile tick(const Projectile &projectile) const
    {
        const Tuple &position = projectile.position() + projectile.velocity();
        const Tuple &velocity = projectile.velocity() + m_gravity + m_wind;
        return Projectile(position, velocity);
    }

private:
    Tuple m_gravity;
    Tuple m_wind;
};

int main()
{
    Tuple start = Point(0, 1, 0);
    Tuple velocity = Vector(1, 1.8, 0).normalize() * 11.25;

    Projectile projectile(start, velocity);

    Tuple gravity = Vector(0, -0.1, 0);
    Tuple wind = Vector(-0.01, 0, 0);
    Environment environment(gravity, wind);

    Canvas canvas(900, 550);

    Color red(1, 0, 0);

    while (projectile.position().y > 0) {
        projectile = environment.tick(projectile);
        int x = round(projectile.position().x);
        int y = canvas.height() - round(projectile.position().y);
        canvas.drawCircle(x, y, 4, red);
    }

    std::cout << canvas.toPPM() << std::endl;

    return 0;
}
