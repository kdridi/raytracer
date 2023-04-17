#include "matrix.hpp"
#include "tuple.hpp"

#include <cstdarg>

using namespace raytracer;

Matrix Matrix::identity(std::size_t size)
{
    Matrix result(size, size);

    for (size_t i = 0; i < size; ++i)
        result[i][i] = 1;

    return result;
}

Matrix Matrix::translation(double x, double y, double z)
{
    Matrix result = Matrix::identity(4);
    result[0][3] = x;
    result[1][3] = y;
    result[2][3] = z;
    return result;
}

Matrix Matrix::scaling(double x, double y, double z)
{
    Matrix result = Matrix::identity(4);
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    return result;
}

Matrix Matrix::rotationX(double radians)
{
    Matrix result = Matrix::identity(4);
    result[1][1] = std::cos(radians);
    result[1][2] = -std::sin(radians);
    result[2][1] = std::sin(radians);
    result[2][2] = std::cos(radians);
    return result;
}

Matrix Matrix::rotationY(double radians)
{
    Matrix result = Matrix::identity(4);
    result[0][0] = std::cos(radians);
    result[0][2] = std::sin(radians);
    result[2][0] = -std::sin(radians);
    result[2][2] = std::cos(radians);
    return result;
}

Matrix Matrix::rotationZ(double radians)
{
    Matrix result = Matrix::identity(4);
    result[0][0] = std::cos(radians);
    result[0][1] = -std::sin(radians);
    result[1][0] = std::sin(radians);
    result[1][1] = std::cos(radians);
    return result;
}

Matrix Matrix::shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
    Matrix result = Matrix::identity(4);
    result[0][1] = xy;
    result[0][2] = xz;
    result[1][0] = yx;
    result[1][2] = yz;
    result[2][0] = zx;
    result[2][1] = zy;
    return result;
}

Matrix::Matrix(size_t rows, size_t cols)
    : m_rows(rows), m_cols(cols)
{
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_matrix[i][j] = 0;
}

Matrix::Matrix(size_t rows, size_t cols, double *values)
    : m_rows(rows), m_cols(cols)
{
    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            m_matrix[i][j] = values[i * cols + j];
}

std::size_t Matrix::rows() const
{
    return m_rows;
}

std::size_t Matrix::cols() const
{
    return m_cols;
}

double *Matrix::operator[](std::size_t row)
{
    return m_matrix[row];
}

bool Matrix::operator==(const Matrix &other) const
{
    if (m_rows != other.m_rows || m_cols != other.m_cols)
        return false;

    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            if (double_equals(m_matrix[i][j], other.m_matrix[i][j]) == false)
                return false;

    return true;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix result(m_rows, other.m_cols);

    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < other.m_cols; ++j)
            for (size_t k = 0; k < m_cols; ++k)
                result.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
    return result;
}

Tuple Matrix::operator*(const Tuple &other) const
{
    Tuple result(0, 0, 0, 0);

    for (size_t i = 0; i < m_rows; ++i) {
        result[i] = 0;
        for (size_t j = 0; j < m_cols; ++j)
            result[i] += m_matrix[i][j] * other[j];
    }
    return result;
}

Matrix Matrix::transpose() const
{
    Matrix result(m_cols, m_rows);

    for (size_t i = 0; i < m_rows; ++i)
        for (size_t j = 0; j < m_cols; ++j)
            result.m_matrix[j][i] = m_matrix[i][j];

    return result;
}

double Matrix::determinant() const
{
    if (m_rows != m_cols)
        return 0;

    if (m_rows == 2)
        return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];

    double result = 0;
    for (size_t i = 0; i < m_cols; ++i)
        result += m_matrix[0][i] * cofactor(0, i);

    return result;
}

Matrix Matrix::submatrix(size_t row, size_t col) const
{
    Matrix result(m_rows - 1, m_cols - 1);

    for (size_t i = 0; i < m_rows; ++i) {
        if (i == row)
            continue;

        for (size_t j = 0; j < m_cols; ++j) {
            if (j == col)
                continue;

            result.m_matrix[i < row ? i : i - 1][j < col ? j : j - 1] = m_matrix[i][j];
        }
    }

    return result;
}

double Matrix::minor(size_t row, size_t col) const
{
    return submatrix(row, col).determinant();
}

double Matrix::cofactor(size_t row, size_t col) const
{
    return minor(row, col) * ((row + col) % 2 == 0 ? 1 : -1);
}

bool Matrix::isInvertible() const
{
    return determinant() != 0;
}

Matrix Matrix::inverse() const
{
    if (!isInvertible())
        return Matrix(0, 0);

    Matrix result(m_rows, m_cols);

    double det = determinant();
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_cols; ++j) {
            result.m_matrix[j][i] = cofactor(i, j) / det;
        }
    }

    return result;
}
