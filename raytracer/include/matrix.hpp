#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <array>
#include <cstddef>

#define MAX_MATRIX_SIZE 4

namespace raytracer {
    class Tuple;

    class Matrix {
    public:
        static Matrix identity(std::size_t);
        static Matrix translation(double, double, double);
        static Matrix scaling(double, double, double);
        static Matrix rotationX(double);
        static Matrix rotationY(double);
        static Matrix rotationZ(double);
        static Matrix shearing(double, double, double, double, double, double);
        static Matrix viewTransform(const Tuple &from, const Tuple &to, const Tuple &up);

    public:
        Matrix(std::size_t rows, std::size_t cols);
        Matrix(std::size_t rows, std::size_t cols, double *values);
        virtual ~Matrix() = default;

        Matrix(const Matrix &) = default;
        Matrix &operator=(const Matrix &) = default;

        Matrix(Matrix &&) = default;
        Matrix &operator=(Matrix &&) = default;

    public:
        std::size_t rows() const;
        std::size_t cols() const;
        double *operator[](std::size_t);
        bool operator==(const Matrix &) const;
        Matrix operator*(const Matrix &) const;
        Tuple operator*(const Tuple &) const;

    public:
        Matrix transpose() const;
        double determinant() const;
        Matrix submatrix(std::size_t, std::size_t) const;
        double minor(std::size_t, std::size_t) const;
        double cofactor(std::size_t, std::size_t) const;
        bool isInvertible() const;
        Matrix inverse() const;

    private:
        std::size_t m_rows;
        std::size_t m_cols;
        double m_matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
    };

} // namespace raytracer

#endif // __MATRIX_HPP__
