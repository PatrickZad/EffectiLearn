#ifndef CORE_COMMON_H
#define CORE_COMMON_H
#include <initializer_list>
namespace patrick
{
    class Vector
    {
    private:
        double* array;
        unsigned int length=0;
    public:
        Vector(double* row, unsigned int length);
        Vector(const Vector& vector);
        Vector(Vector&& vector);
        ~Vector();
        
        Vector& operator=(const Vector& vector);
        Vector& operator=(Vector&& vector);
        Vector operator+(const Vector& vector);
        Vector& operator+=(const Vector& vector);
        double operator*(const Vector& vector);
        Vector operator-(const Vector& vector);
        Vector& operator-=(const Vector& vector);
        double& operator[](unsigned int index);
    };
} // namespace patrick

#endif