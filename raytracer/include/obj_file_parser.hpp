#ifndef __OBJ_FILE_PARSER_HPP__
#define __OBJ_FILE_PARSER_HPP__

#include "utils.hpp"

namespace raytracer {
    class Triangle;

    class OBJFileParser {
    private:
        OBJFileParser(const std::vector<Point> &vertices, const std::vector<Vector> &normals, const std::vector<Triangle> &faces)
            : vertices(vertices), normals(normals), faces(faces) {}

    public:
        static OBJFileParser ParseFile(const std::string &filePath);
        static OBJFileParser ParseString(const std::string &fileContent);

        ~OBJFileParser() = default;

        OBJFileParser(const OBJFileParser &other) = default;
        OBJFileParser &operator=(const OBJFileParser &other) = default;

        std::vector<Point> vertices;
        std::vector<Vector> normals;
        std::vector<Triangle> faces;
    };

} // namespace raytracer

#endif // __OBJ_FILE_PARSER_HPP__
