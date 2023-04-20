#include "raytracer.hpp"

using namespace raytracer;

OBJFileParser OBJFileParser::ParseFile(const std::string &filePath)
{
    std::ifstream objFileStream(filePath);
    std::stringstream objFileContent;
    objFileContent << objFileStream.rdbuf();
    return ParseString(objFileContent.str());
}

OBJFileParser OBJFileParser::ParseString(const std::string &fileContent)
{
    std::vector<Point> vertices;
    std::vector<Vector> normals;
    std::vector<Triangle> faces;

    std::stringstream objFileStream(fileContent);
    std::string line;
    while (std::getline(objFileStream, line)) {
        std::stringstream lineStream(line);
        std::string lineType;
        lineStream >> lineType;

        if (lineType == "v") {
            double x, y, z;
            lineStream >> x >> y >> z;
            vertices.push_back(Point(x, y, z));
        } else if (lineType == "vn") {
            double x, y, z;
            lineStream >> x >> y >> z;
            normals.push_back(Vector(x, y, z));
        } else if (lineType == "f") {
            std::vector<int> face;
            std::string faceVertex;
            while (lineStream >> faceVertex) {
                std::stringstream faceVertexStream(faceVertex);
                std::string faceVertexIndex;
                std::getline(faceVertexStream, faceVertexIndex, '/');
                face.push_back(std::stoi(faceVertexIndex));
            }

            for (int i = 2; i < face.size(); i++) {
                auto p1 = vertices[face[0] - 1];
                auto p2 = vertices[face[i - 1] - 1];
                auto p3 = vertices[face[i] - 1];
                faces.push_back(Triangle(p1, p2, p3));
            }
        }
    }

    return OBJFileParser(vertices, normals, faces);
}
