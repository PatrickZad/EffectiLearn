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
        Vector(double* row, unsigned long length);
        Vector(unsigned long length, double init=0);
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
        double& operator[](unsigned long index);
        long size();
        Vector& concat(const Vector& vec);
    };
    
    class DistanceFunc
    {
    public:
        double operator()(Vector& vec0, Vector& vec1);
    };
    
} // namespace patrick

#endif