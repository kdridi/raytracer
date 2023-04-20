#include "canvas.hpp"

using namespace raytracer;

Canvas::Canvas(int width, int height)
    : m_width(width), m_height(height)
{
    for (int y = 0; y < m_height; y++) {
        std::vector<Color> row;
        for (int x = 0; x < m_width; x++)
            row.push_back(Color(0, 0, 0));
        m_pixels.push_back(row);
    }
}

int Canvas::width() const
{
    return m_width;
}

int Canvas::height() const
{
    return m_height;
}

Color Canvas::pixelAt(int x, int y) const
{
    return m_pixels[y][x];
}

void Canvas::writePixel(int x, int y, const Color &color)
{
    m_pixels[y][x] = color;
}

void Canvas::drawCircle(int x, int y, int radius, const Color &color)
{
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i * i + j * j <= radius * radius) {
                int px = x + i;
                int py = y + j;
                if (px >= 0 && px < m_width && py >= 0 && py < m_height)
                    writePixel(px, py, color);
            }
        }
    }
}

std::string Canvas::toPPM() const
{
    std::stringstream ss;
    ss << "P3" << std::endl;
    ss << m_width << " " << m_height << std::endl;
    ss << "255" << std::endl;

    for (int y = 0; y < m_height; y++) {
        std::list<std::string> colors;
        for (int x = 0; x < m_width; x++) {
            Color c = pixelAt(x, y);

            int r = static_cast<int>(std::max(0.0, std::min(255.0, std::floor(c.red() * 256))));
            int g = static_cast<int>(std::max(0.0, std::min(255.0, std::floor(c.green() * 256))));
            int b = static_cast<int>(std::max(0.0, std::min(255.0, std::floor(c.blue() * 256))));

            colors.push_back(std::to_string(r));
            colors.push_back(std::to_string(g));
            colors.push_back(std::to_string(b));
        }

        std::string color;
        std::stringstream line;

        color = colors.front();
        colors.pop_front();

        line << color;

        while (!colors.empty()) {
            color = colors.front();
            colors.pop_front();

            if (line.str().length() + color.length() + 1 > 70) {
                ss << line.str() << std::endl;
                line = std::stringstream();
                line << color;
            } else {
                line << " " << color;
            }
        }
        ss << line.str() << std::endl;
    }

    return ss.str();
}

void Canvas::savePPM(const std::string &filePath) const
{
    std::ofstream file(filePath);
    file << toPPM();
    file.close();
}
