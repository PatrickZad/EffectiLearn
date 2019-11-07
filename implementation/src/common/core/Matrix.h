#ifndef COMMON_CORE_MATRIX_H
#define COMMON_CORE_MATRIX_H
#include "Vector.h"
#include <vector>
namespace patrick
{
    static const short VECTOR_ROW=0;
    static const short VECTOR_COLUMN=1;
    class Matrix
    {
    private:
        unsigned long width=0;
        unsigned long length=0;
        double* start=nullptr;
    public:
        Matrix(){};
        Matrix(unsigned long squareWidth);
        Matrix(unsigned long  length, unsigned long width, double init=0);
        Matrix(Vector& vec, short shape=VECTOR_COLUMN);
        Matrix(const Matrix& m);
        Matrix(Matrix&& m);
        ~Matrix();
        unsigned long getLength()const;
        unsigned long getWidth()const;

        Matrix& operator=(const Matrix& m);
        Matrix& operator=(Matrix&& m);
        Matrix& operator+=(const Matrix& m);
        Matrix& operator-=(const Matrix& m);
        double* operator[](unsigned long index)const;
        Matrix transposition();
        Matrix inverse();
        double det();
        Matrix adjugate();
        std::vector<Vector> getRows();
        std::vector<Vector> getColumns();
    };

    Matrix operator*(const Matrix& m1, const Matrix& m2);
    Matrix operator*(const Matrix& m, double num);
    Matrix operator*(double num, const Matrix& m);
    Matrix operator+(const Matrix& m1, const Matrix& m2);
    Matrix operator-(const Matrix& m1, const Matrix& m2);
    Matrix operator/(const Matrix& m, double num);
} // namespace patrick

#endif