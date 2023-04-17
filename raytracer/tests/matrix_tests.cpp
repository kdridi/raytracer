#include "raytracer.hpp"

#include <gmock/gmock.h>

class MatrixTest : public testing::Test {};

// Constructing and inspecting a 4x4 matrix
TEST_F(MatrixTest, Constructing_and_inspecting_a_4x4_matrix)
{
    double values[] =
        {1, 2, 3, 4,
         5.5, 6.5, 7.5, 8.5,
         9, 10, 11, 12,
         13.5, 14.5, 15.5, 16.5};

    raytracer::Matrix m(4, 4, values);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][3], 4);
    EXPECT_EQ(m[1][0], 5.5);
    EXPECT_EQ(m[1][2], 7.5);
    EXPECT_EQ(m[2][2], 11);
    EXPECT_EQ(m[3][0], 13.5);
    EXPECT_EQ(m[3][2], 15.5);
}

// A 2x2 matrix ought to be representable
TEST_F(MatrixTest, A_2x2_matrix_ought_to_be_representable)
{
    double values[] =
        {-3, 5,
         1, -2};

    raytracer::Matrix m(2, 2, values);
    EXPECT_EQ(m[0][0], -3);
    EXPECT_EQ(m[0][1], 5);
    EXPECT_EQ(m[1][0], 1);
    EXPECT_EQ(m[1][1], -2);
}

// A 3x3 matrix ought to be representable
TEST_F(MatrixTest, A_3x3_matrix_ought_to_be_representable)
{
    double values[] =
        {-3, 5, 0,
         1, -2, -7,
         0, 1, 1};

    raytracer::Matrix m(3, 3, values);
    EXPECT_EQ(m[0][0], -3);
    EXPECT_EQ(m[1][1], -2);
    EXPECT_EQ(m[2][2], 1);
}

// Matrix equality with identical matrices
TEST_F(MatrixTest, Matrix_equality_with_identical_matrices)
{
    double values[] =
        {1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2};

    raytracer::Matrix a(4, 4, values);
    raytracer::Matrix b(4, 4, values);
    EXPECT_TRUE(a == b);
}

// Matrix equality with different matrices
TEST_F(MatrixTest, Matrix_equality_with_different_matrices)
{
    double values1[] =
        {1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2};

    double values2[] =
        {2, 3, 4, 5,
         6, 7, 8, 9,
         8, 7, 6, 5,
         4, 3, 2, 1};

    raytracer::Matrix a(4, 4, values1);
    raytracer::Matrix b(4, 4, values2);
    EXPECT_FALSE(a == b);
}

// Multiplying two matrices
TEST_F(MatrixTest, Multiplying_two_matrices)
{
    double values1[] =
        {1, 2, 3, 4,
         5, 6, 7, 8,
         9, 8, 7, 6,
         5, 4, 3, 2};

    double values2[] =
        {-2, 1, 2, 3,
         3, 2, 1, -1,
         4, 3, 6, 5,
         1, 2, 7, 8};

    double values3[] =
        {20, 22, 50, 48,
         44, 54, 114, 108,
         40, 58, 110, 102,
         16, 26, 46, 42};

    raytracer::Matrix a(4, 4, values1);
    raytracer::Matrix b(4, 4, values2);
    raytracer::Matrix c(4, 4, values3);
    EXPECT_TRUE(a * b == c);
}

// A matrix multiplied by a tuple
TEST_F(MatrixTest, A_matrix_multiplied_by_a_tuple)
{
    double values[] =
        {1, 2, 3, 4,
         2, 4, 4, 2,
         8, 6, 4, 1,
         0, 0, 0, 1};

    raytracer::Matrix a(4, 4, values);
    raytracer::Tuple b(1, 2, 3, 1);
    raytracer::Tuple c(18, 24, 33, 1);
    EXPECT_TRUE(a * b == c);
}

// Multiplying a matrix by the identity matrix
TEST_F(MatrixTest, Multiplying_a_matrix_by_the_identity_matrix)
{
    double values[] =
        {0, 1, 2, 4,
         1, 2, 4, 8,
         2, 4, 8, 16,
         4, 8, 16, 32};

    raytracer::Matrix a(4, 4, values);
    raytracer::Matrix b(4, 4, values);
    EXPECT_TRUE(a * raytracer::Matrix::identity(4) == b);
}

// Multiplying the identity matrix by a tuple
TEST_F(MatrixTest, Multiplying_the_identity_matrix_by_a_tuple)
{
    raytracer::Tuple a(1, 2, 3, 4);
    EXPECT_TRUE(raytracer::Matrix::identity(4) * a == a);
}

// Transposing a matrix
TEST_F(MatrixTest, Transposing_a_matrix)
{
    double values1[] =
        {0, 9, 3, 0,
         9, 8, 0, 8,
         1, 8, 5, 3,
         0, 0, 5, 8};

    double values2[] =
        {0, 9, 1, 0,
         9, 8, 8, 0,
         3, 0, 5, 5,
         0, 8, 3, 8};

    raytracer::Matrix a(4, 4, values1);
    raytracer::Matrix b(4, 4, values2);
    EXPECT_TRUE(a.transpose() == b);
}

// Transposing the identity matrix
TEST_F(MatrixTest, Transposing_the_identity_matrix)
{
    raytracer::Matrix a = raytracer::Matrix::identity(4);
    EXPECT_TRUE(a.transpose() == a);
}

// Calculating the determinant of a 2x2 matrix
TEST_F(MatrixTest, Calculating_the_determinant_of_a_2x2_matrix)
{
    double values[] =
        {1, 5,
         -3, 2};

    raytracer::Matrix a(2, 2, values);
    EXPECT_EQ(a.determinant(), 17);
}

// A submatrix of a 3x3 matrix is a 2x2 matrix
TEST_F(MatrixTest, A_submatrix_of_a_3x3_matrix_is_a_2x2_matrix)
{
    double values[] =
        {1, 5, 0,
         -3, 2, 7,
         0, 6, -3};

    raytracer::Matrix a(3, 3, values);
    double values2[] =
        {-3, 2,
         0, 6};

    raytracer::Matrix b(2, 2, values2);
    EXPECT_TRUE(a.submatrix(0, 2) == b);
}

// A submatrix of a 4x4 matrix is a 3x3 matrix
TEST_F(MatrixTest, A_submatrix_of_a_4x4_matrix_is_a_3x3_matrix)
{
    double values[] =
        {-6, 1, 1, 6,
         -8, 5, 8, 6,
         -1, 0, 8, 2,
         -7, 1, -1, 1};

    raytracer::Matrix a(4, 4, values);
    double values2[] =
        {-6, 1, 6,
         -8, 8, 6,
         -7, -1, 1};

    raytracer::Matrix b(3, 3, values2);
    EXPECT_TRUE(a.submatrix(2, 1) == b);
}

// Calculating a minor of a 3x3 matrix
TEST_F(MatrixTest, Calculating_a_minor_of_a_3x3_matrix)
{
    double values[] =
        {3, 5, 0,
         2, -1, -7,
         6, -1, 5};

    raytracer::Matrix a(3, 3, values);
    raytracer::Matrix b = a.submatrix(1, 0);
    EXPECT_EQ(b.determinant(), 25);
    EXPECT_EQ(a.minor(1, 0), 25);
}

// Calculating a cofactor of a 3x3 matrix
TEST_F(MatrixTest, Calculating_a_cofactor_of_a_3x3_matrix)
{
    double values[] =
        {3, 5, 0,
         2, -1, -7,
         6, -1, 5};

    raytracer::Matrix a(3, 3, values);
    EXPECT_EQ(a.minor(0, 0), -12);
    EXPECT_EQ(a.cofactor(0, 0), -12);
    EXPECT_EQ(a.minor(1, 0), 25);
    EXPECT_EQ(a.cofactor(1, 0), -25);
}

// Calculating the determinant of a 3x3 matrix
TEST_F(MatrixTest, Calculating_the_determinant_of_a_3x3_matrix)
{
    double values[] =
        {1, 2, 6,
         -5, 8, -4,
         2, 6, 4};

    raytracer::Matrix a(3, 3, values);
    EXPECT_EQ(a.cofactor(0, 0), 56);
    EXPECT_EQ(a.cofactor(0, 1), 12);
    EXPECT_EQ(a.cofactor(0, 2), -46);
    EXPECT_EQ(a.determinant(), -196);
}

// Calculating the determinant of a 4x4 matrix
TEST_F(MatrixTest, Calculating_the_determinant_of_a_4x4_matrix)
{
    double values[] =
        {-2, -8, 3, 5,
         -3, 1, 7, 3,
         1, 2, -9, 6,
         -6, 7, 7, -9};

    raytracer::Matrix a(4, 4, values);
    EXPECT_EQ(a.cofactor(0, 0), 690);
    EXPECT_EQ(a.cofactor(0, 1), 447);
    EXPECT_EQ(a.cofactor(0, 2), 210);
    EXPECT_EQ(a.cofactor(0, 3), 51);
    EXPECT_EQ(a.determinant(), -4071);
}

// Testing an invertible matrix for invertibility
TEST_F(MatrixTest, Testing_an_invertible_matrix_for_invertibility)
{
    double values[] =
        {6, 4, 4, 4,
         5, 5, 7, 6,
         4, -9, 3, -7,
         9, 1, 7, -6};

    raytracer::Matrix a(4, 4, values);
    EXPECT_EQ(a.determinant(), -2120);
    EXPECT_TRUE(a.isInvertible());
}

// Testing a noninvertible matrix for invertibility
TEST_F(MatrixTest, Testing_a_noninvertible_matrix_for_invertibility)
{
    double values[] =
        {-4, 2, -2, -3,
         9, 6, 2, 6,
         0, -5, 1, -5,
         0, 0, 0, 0};

    raytracer::Matrix a(4, 4, values);
    EXPECT_EQ(a.determinant(), 0);
    EXPECT_FALSE(a.isInvertible());
}

// Calculating the inverse of a matrix
TEST_F(MatrixTest, Calculating_the_inverse_of_a_matrix)
{
    double values[] =
        {-5, 2, 6, -8,
         1, -5, 1, 8,
         7, 7, -6, -7,
         1, -3, 7, 4};

    raytracer::Matrix a(4, 4, values);
    raytracer::Matrix b = a.inverse();
    double values2[] =
        {0.21805, 0.45113, 0.24060, -0.04511,
         -0.80827, -1.45677, -0.44361, 0.52068,
         -0.07895, -0.22368, -0.05263, 0.19737,
         -0.52256, -0.81391, -0.30075, 0.30639};

    raytracer::Matrix c(4, 4, values2);
    EXPECT_TRUE(b == c);
}

// Calculating the inverse of another matrix
TEST_F(MatrixTest, Calculating_the_inverse_of_another_matrix)
{
    double values[] =
        {8, -5, 9, 2,
         7, 5, 6, 1,
         -6, 0, 9, 6,
         -3, 0, -9, -4};

    raytracer::Matrix a(4, 4, values);
    raytracer::Matrix b = a.inverse();
    double values2[] =
        {-0.15385, -0.15385, -0.28205, -0.53846,
         -0.07692, 0.12308, 0.02564, 0.03077,
         0.35897, 0.35897, 0.43590, 0.92308,
         -0.69231, -0.69231, -0.76923, -1.92308};

    raytracer::Matrix c(4, 4, values2);
    EXPECT_TRUE(b == c);
}

// Calculating the inverse of a third matrix
TEST_F(MatrixTest, Calculating_the_inverse_of_a_third_matrix)
{
    double values[] =
        {9, 3, 0, 9,
         -5, -2, -6, -3,
         -4, 9, 6, 4,
         -7, 6, 6, 2};

    raytracer::Matrix a(4, 4, values);
    raytracer::Matrix b = a.inverse();
    double values2[] =
        {-0.04074, -0.07778, 0.14444, -0.22222,
         -0.07778, 0.03333, 0.36667, -0.33333,
         -0.02901, -0.14630, -0.10926, 0.12963,
         0.17778, 0.06667, -0.26667, 0.33333};

    raytracer::Matrix c(4, 4, values2);
    EXPECT_TRUE(b == c);
}

// Multiplying a product by its inverse
TEST_F(MatrixTest, Multiplying_a_product_by_its_inverse)
{
    double values[] =
        {3, -9, 7, 3,
         3, -8, 2, -9,
         -4, 4, 4, 1,
         -6, 5, -1, 1};

    raytracer::Matrix a(4, 4, values);
    double values2[] =
        {8, 2, 2, 2,
         3, -1, 7, 0,
         7, 0, 5, 4,
         6, -2, 0, 5};

    raytracer::Matrix b(4, 4, values2);
    raytracer::Matrix c = a * b;
    raytracer::Matrix d = c * b.inverse();
    EXPECT_TRUE(a == d);
}

// Multiplying by a translation matrix
TEST_F(MatrixTest, Multiplying_by_a_translation_matrix)
{
    raytracer::Matrix transform = raytracer::Matrix::translation(5, -3, 2);
    raytracer::Tuple p = raytracer::Tuple::point(-3, 4, 5);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(2, 1, 7));
}

// Multiplying by the inverse of a translation matrix
TEST_F(MatrixTest, Multiplying_by_the_inverse_of_a_translation_matrix)
{
    raytracer::Matrix transform = raytracer::Matrix::translation(5, -3, 2);
    raytracer::Matrix inv = transform.inverse();
    raytracer::Tuple p = raytracer::Tuple::point(-3, 4, 5);
    EXPECT_TRUE(inv * p == raytracer::Tuple::point(-8, 7, 3));
}

// Translation does not affect vectors
TEST_F(MatrixTest, Translation_does_not_affect_vectors)
{
    raytracer::Matrix transform = raytracer::Matrix::translation(5, -3, 2);
    raytracer::Tuple v = raytracer::Tuple::vector(-3, 4, 5);
    EXPECT_TRUE(transform * v == v);
}

// A scaling matrix applied to a point
TEST_F(MatrixTest, A_scaling_matrix_applied_to_a_point)
{
    raytracer::Matrix transform = raytracer::Matrix::scaling(2, 3, 4);
    raytracer::Tuple p = raytracer::Tuple::point(-4, 6, 8);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(-8, 18, 32));
}

// A scaling matrix applied to a vector
TEST_F(MatrixTest, A_scaling_matrix_applied_to_a_vector)
{
    raytracer::Matrix transform = raytracer::Matrix::scaling(2, 3, 4);
    raytracer::Tuple v = raytracer::Tuple::vector(-4, 6, 8);
    EXPECT_TRUE(transform * v == raytracer::Tuple::vector(-8, 18, 32));
}

// Multiplying by the inverse of a scaling matrix
TEST_F(MatrixTest, Multiplying_by_the_inverse_of_a_scaling_matrix)
{
    raytracer::Matrix transform = raytracer::Matrix::scaling(2, 3, 4);
    raytracer::Matrix inv = transform.inverse();
    raytracer::Tuple v = raytracer::Tuple::vector(-4, 6, 8);
    EXPECT_TRUE(inv * v == raytracer::Tuple::vector(-2, 2, 2));
}

// Reflection is scaling by a negative value
TEST_F(MatrixTest, Reflection_is_scaling_by_a_negative_value)
{
    raytracer::Matrix transform = raytracer::Matrix::scaling(-1, 1, 1);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(-2, 3, 4));
}

// Rotating a point around the x axis
TEST_F(MatrixTest, Rotating_a_point_around_the_x_axis)
{
    raytracer::Tuple p = raytracer::Tuple::point(0, 1, 0);
    raytracer::Matrix half_quarter = raytracer::Matrix::rotationX(M_PI / 4);
    raytracer::Matrix full_quarter = raytracer::Matrix::rotationX(M_PI / 2);
    EXPECT_TRUE(half_quarter * p == raytracer::Tuple::point(0, std::sqrt(2) / 2, std::sqrt(2) / 2));
    EXPECT_TRUE(full_quarter * p == raytracer::Tuple::point(0, 0, 1));
}

// The inverse of an x-rotation rotates in the opposite direction
TEST_F(MatrixTest, The_inverse_of_an_x_rotation_rotates_in_the_opposite_direction)
{
    raytracer::Tuple p = raytracer::Tuple::point(0, 1, 0);
    raytracer::Matrix half_quarter = raytracer::Matrix::rotationX(M_PI / 4);
    raytracer::Matrix inv = half_quarter.inverse();
    EXPECT_TRUE(inv * p == raytracer::Tuple::point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
}

// Rotating a point around the y axis
TEST_F(MatrixTest, Rotating_a_point_around_the_y_axis)
{
    raytracer::Tuple p = raytracer::Tuple::point(0, 0, 1);
    raytracer::Matrix half_quarter = raytracer::Matrix::rotationY(M_PI / 4);
    raytracer::Matrix full_quarter = raytracer::Matrix::rotationY(M_PI / 2);
    EXPECT_TRUE(half_quarter * p == raytracer::Tuple::point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
    EXPECT_TRUE(full_quarter * p == raytracer::Tuple::point(1, 0, 0));
}

// Rotating a point around the z axis
TEST_F(MatrixTest, Rotating_a_point_around_the_z_axis)
{
    raytracer::Tuple p = raytracer::Tuple::point(0, 1, 0);
    raytracer::Matrix half_quarter = raytracer::Matrix::rotationZ(M_PI / 4);
    raytracer::Matrix full_quarter = raytracer::Matrix::rotationZ(M_PI / 2);
    EXPECT_TRUE(half_quarter * p == raytracer::Tuple::point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
    EXPECT_TRUE(full_quarter * p == raytracer::Tuple::point(-1, 0, 0));
}

// A shearing transformation moves x in proportion to y
TEST_F(MatrixTest, A_shearing_transformation_moves_x_in_proportion_to_y)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(1, 0, 0, 0, 0, 0);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(5, 3, 4));
}

// A shearing transformation moves x in proportion to z
TEST_F(MatrixTest, A_shearing_transformation_moves_x_in_proportion_to_z)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(0, 1, 0, 0, 0, 0);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(6, 3, 4));
}

// A shearing transformation moves y in proportion to x
TEST_F(MatrixTest, A_shearing_transformation_moves_y_in_proportion_to_x)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(0, 0, 1, 0, 0, 0);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(2, 5, 4));
}

// A shearing transformation moves y in proportion to z
TEST_F(MatrixTest, A_shearing_transformation_moves_y_in_proportion_to_z)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(0, 0, 0, 1, 0, 0);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(2, 7, 4));
}

// A shearing transformation moves z in proportion to x
TEST_F(MatrixTest, A_shearing_transformation_moves_z_in_proportion_to_x)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(0, 0, 0, 0, 1, 0);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(2, 3, 6));
}

// A shearing transformation moves z in proportion to y
TEST_F(MatrixTest, A_shearing_transformation_moves_z_in_proportion_to_y)
{
    raytracer::Matrix transform = raytracer::Matrix::shearing(0, 0, 0, 0, 0, 1);
    raytracer::Tuple p = raytracer::Tuple::point(2, 3, 4);
    EXPECT_TRUE(transform * p == raytracer::Tuple::point(2, 3, 7));
}

// Individual transformations are applied in sequence
TEST_F(MatrixTest, Individual_transformations_are_applied_in_sequence)
{
    raytracer::Tuple p = raytracer::Tuple::point(1, 0, 1);
    raytracer::Matrix A = raytracer::Matrix::rotationX(M_PI / 2);
    raytracer::Matrix B = raytracer::Matrix::scaling(5, 5, 5);
    raytracer::Matrix C = raytracer::Matrix::translation(10, 5, 7);
    raytracer::Tuple p2 = A * p;
    EXPECT_TRUE(p2 == raytracer::Tuple::point(1, -1, 0));
    raytracer::Tuple p3 = B * p2;
    EXPECT_TRUE(p3 == raytracer::Tuple::point(5, -5, 0));
    raytracer::Tuple p4 = C * p3;
    EXPECT_TRUE(p4 == raytracer::Tuple::point(15, 0, 7));
}

// Chained transformations must be applied in reverse order
TEST_F(MatrixTest, Chained_transformations_must_be_applied_in_reverse_order)
{
    raytracer::Tuple p = raytracer::Tuple::point(1, 0, 1);
    raytracer::Matrix A = raytracer::Matrix::rotationX(M_PI / 2);
    raytracer::Matrix B = raytracer::Matrix::scaling(5, 5, 5);
    raytracer::Matrix C = raytracer::Matrix::translation(10, 5, 7);
    raytracer::Matrix T = C * B * A;
    EXPECT_TRUE(T * p == raytracer::Tuple::point(15, 0, 7));
}
