#ifndef CORE_COMMON_H
#define CORE_COMMON_H
#include <initializer_list>
namespace patrick
{
    class Vector
    {
    private:
        double* array;
        long length=0;
    public:
        Vector(double* row, long length);
        Vector(long length, double init=0);
        Vector(const Vector& vector);
        Vector(Vector&& vector);
        ~Vector();
        
        Vector& operator=(const Vector& vector);
        Vector& operator=(Vector&& vector);
        Vector operator+(const Vector& vector);
        Vector& operator+=(const Vector& vector);
        double operator*(const Vector& vector);
        Vector& operator*(double factor);
        Vector operator-(const Vector& vector);
        Vector& operator-=(const Vector& vector);
        double& operator[](long index);
        long size();
    };
} // namespace patrick

#endif