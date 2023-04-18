#include "raytracer.hpp"

#include <gmock/gmock.h>

class CanvasTest : public testing::Test {};

// Creating a canvas
TEST_F(CanvasTest, Creating_a_canvas)
{
    raytracer::Canvas c(10, 20);
    EXPECT_EQ(c.width(), 10);
    EXPECT_EQ(c.height(), 20);
    for (int y = 0; y < c.height(); y++)
        for (int x = 0; x < c.width(); x++)
            EXPECT_EQ(c.pixelAt(x, y), raytracer::Color(0, 0, 0));
}

// Writing pixels to a canvas
TEST_F(CanvasTest, Writing_pixels_to_a_canvas)
{
    raytracer::Canvas c(10, 20);
    raytracer::Color red(1, 0, 0);
    c.writePixel(2, 3, red);
    EXPECT_EQ(c.pixelAt(2, 3), red);
}

// Constructing the PPM header
TEST_F(CanvasTest, Constructing_the_PPM_header)
{
    raytracer::Canvas c(5, 3);
    std::string ppm = c.toPPM();

    std::vector<std::string> lines;
    lines.push_back("P3");
    lines.push_back("5 3");
    lines.push_back("255");

    for (std::string line : lines) {
        size_t pos = ppm.find(line);
        EXPECT_NE(pos, std::string::npos);
        ppm = ppm.substr(pos + line.length());
    }
}

// Constructing the PPM pixel data
TEST_F(CanvasTest, Constructing_the_PPM_pixel_data)
{
    raytracer::Canvas c(5, 3);
    raytracer::Color c1(1.5, 0, 0);
    raytracer::Color c2(0, 0.5, 0);
    raytracer::Color c3(-0.5, 0, 1);
    c.writePixel(0, 0, c1);
    c.writePixel(2, 1, c2);
    c.writePixel(4, 2, c3);
    std::string ppm = c.toPPM();

    std::vector<std::string> lines;
    lines.push_back("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    lines.push_back("0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    lines.push_back("0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");

    for (std::string line : lines) {
        size_t pos = ppm.find(line);
        EXPECT_NE(pos, std::string::npos);
        ppm = ppm.substr(pos + line.length());
    }
}

// Splitting long lines in PPM files
TEST_F(CanvasTest, Splitting_long_lines_in_PPM_files)
{
    raytracer::Canvas c(10, 2);
    raytracer::Color color(1, 0.8, 0.6);
    for (int y = 0; y < c.height(); y++)
        for (int x = 0; x < c.width(); x++)
            c.writePixel(x, y, color);
    std::string ppm = c.toPPM();

    std::vector<std::string> lines;
    lines.push_back("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
    lines.push_back("153 255 204 153 255 204 153 255 204 153 255 204 153");
    lines.push_back("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
    lines.push_back("153 255 204 153 255 204 153 255 204 153 255 204 153");

    for (std::string line : lines) {
        size_t pos = ppm.find(line);
        EXPECT_NE(pos, std::string::npos);
        ppm = ppm.substr(pos + line.length());
    }
}

// PPM files are terminated by a newline character
TEST_F(CanvasTest, PPM_files_are_terminated_by_a_newline_character)
{
    raytracer::Canvas c(5, 3);
    std::string ppm = c.toPPM();
    EXPECT_EQ(ppm[ppm.length() - 1], '\n');
}
