#ifndef __CANVAS_HPP__
#define __CANVAS_HPP__

#include "color.hpp"
#include "utils.hpp"

namespace raytracer {

    class Canvas {
    public:
        Canvas(int width, int height);
        virtual ~Canvas() = default;

        Canvas(const Canvas &);
        Canvas &operator=(const Canvas &);

        Canvas(Canvas &&);
        Canvas &operator=(Canvas &&);

    public:
        int width() const;
        int height() const;
        Color pixelAt(int, int) const;
        void writePixel(int, int, const Color &);

    public:
        std::string toPPM() const;

    private:
        int m_width;
        int m_height;
        std::vector<std::vector<Color>> m_pixels;
    };

} // namespace raytracer

#endif // __CANVAS_HPP__