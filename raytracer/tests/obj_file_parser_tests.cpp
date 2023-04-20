#include "raytracer.hpp"

#include <gmock/gmock.h>

class OBJFileParserTest : public ::testing::Test {};

// Ignoring unrecognized lines
TEST_F(OBJFileParserTest, IgnoringUnrecognizedLines)
{
    std::stringstream objFileStream;
    objFileStream << "There was a young lady named Bright" << std::endl;
    objFileStream << "Who traveled much faster than light" << std::endl;
    objFileStream << "She set out one day" << std::endl;
    objFileStream << "In a relative way" << std::endl;
    objFileStream << "And came back the previous night" << std::endl;

    raytracer::OBJFileParser parser(raytracer::OBJFileParser::ParseString(objFileStream.str()));
    ASSERT_TRUE(parser.vertices.size() == 0);
    ASSERT_TRUE(parser.normals.size() == 0);
    ASSERT_TRUE(parser.faces.size() == 0);
}

// Vertex records
TEST_F(OBJFileParserTest, VertexRecords)
{
    std::stringstream objFileStream;
    objFileStream << "v -1 1 0" << std::endl;
    objFileStream << "v -1.0000 0.5000 0.0000" << std::endl;
    objFileStream << "v 1 0 0" << std::endl;
    objFileStream << "v 1 1 0" << std::endl;

    raytracer::OBJFileParser parser(raytracer::OBJFileParser::ParseString(objFileStream.str()));
    ASSERT_TRUE(parser.vertices.size() == 4);
    ASSERT_TRUE(parser.vertices[0] == raytracer::Point(-1, 1, 0));
    ASSERT_TRUE(parser.vertices[1] == raytracer::Point(-1, 0.5, 0));
    ASSERT_TRUE(parser.vertices[2] == raytracer::Point(1, 0, 0));
    ASSERT_TRUE(parser.vertices[3] == raytracer::Point(1, 1, 0));
}

// Parsing Triangle Faces
TEST_F(OBJFileParserTest, ParsingTriangleFaces)
{
    std::stringstream objFileStream;
    objFileStream << "v -1 1 0" << std::endl;
    objFileStream << "v -1 0 0" << std::endl;
    objFileStream << "v 1 0 0" << std::endl;
    objFileStream << "v 1 1 0" << std::endl;
    objFileStream << std::endl;
    objFileStream << "f 1 2 3" << std::endl;
    objFileStream << "f 1 3 4" << std::endl;

    raytracer::OBJFileParser parser(raytracer::OBJFileParser::ParseString(objFileStream.str()));
    ASSERT_TRUE(parser.faces.size() == 2);
    ASSERT_TRUE(parser.faces[0].p1 == parser.vertices[0]);
    ASSERT_TRUE(parser.faces[0].p2 == parser.vertices[1]);
    ASSERT_TRUE(parser.faces[0].p3 == parser.vertices[2]);
    ASSERT_TRUE(parser.faces[1].p1 == parser.vertices[0]);
    ASSERT_TRUE(parser.faces[1].p2 == parser.vertices[2]);
    ASSERT_TRUE(parser.faces[1].p3 == parser.vertices[3]);
}

// Triangulating Polygons
TEST_F(OBJFileParserTest, TriangulatingPolygons)
{
    std::stringstream objFileStream;
    objFileStream << "v -1 1 0" << std::endl;
    objFileStream << "v -1 0 0" << std::endl;
    objFileStream << "v 1 0 0" << std::endl;
    objFileStream << "v 1 1 0" << std::endl;
    objFileStream << "v 0 2 0" << std::endl;
    objFileStream << std::endl;
    objFileStream << "f 1 2 3 4 5" << std::endl;

    raytracer::OBJFileParser parser(raytracer::OBJFileParser::ParseString(objFileStream.str()));
    ASSERT_TRUE(parser.faces.size() == 3);
    ASSERT_TRUE(parser.faces[0].p1 == parser.vertices[0]);
    ASSERT_TRUE(parser.faces[0].p2 == parser.vertices[1]);
    ASSERT_TRUE(parser.faces[0].p3 == parser.vertices[2]);
    ASSERT_TRUE(parser.faces[1].p1 == parser.vertices[0]);
    ASSERT_TRUE(parser.faces[1].p2 == parser.vertices[2]);
    ASSERT_TRUE(parser.faces[1].p3 == parser.vertices[3]);
    ASSERT_TRUE(parser.faces[2].p1 == parser.vertices[0]);
    ASSERT_TRUE(parser.faces[2].p2 == parser.vertices[3]);
    ASSERT_TRUE(parser.faces[2].p3 == parser.vertices[4]);
}
