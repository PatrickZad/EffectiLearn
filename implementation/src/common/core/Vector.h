#ifndef COMMON_CORE_VECTOR_H
#define COMMON_CORE_VECTOR_H
#include <vector>
namespace patrick
{
    class Vector
    {
    protected:
        double* array;
        unsigned long length;
    public:
        Vector() : array{nullptr}, length{0}{};
        Vector(std::vector<double> stdvec);
        Vector(double* row, unsigned long length);
        Vector(unsigned long length, double init=0);
        Vector(const Vector& vector);
        Vector(Vector&& vector);
        ~Vector();
        
        Vector& operator=(const Vector& vector);
        Vector& operator=(Vector&& vector);
        Vector& operator+=(const Vector& vector);
        Vector& operator-=(const Vector& vector);
        double& operator[](unsigned long index)const;
        
        unsigned long size()const;
        Vector& concat(const Vector& vec);
        void append(double value);
    };

    double operator*(const Vector& v1,const  Vector& v2);
    Vector operator*(const Vector& v,double num);
    Vector operator*(double num, const Vector& v);
    Vector operator+(const Vector& v1, const Vector& v2);
    Vector operator-(const Vector& v1, const Vector& v2);
    bool operator==(const Vector& v1, const Vector& v2);
    
    class LabledVector : public Vector
    {
    public:
        long long lable;
    public:
        LabledVector(double* row, unsigned long length,long long lable) 
            : Vector{row, length}, lable{lable}{};
        LabledVector(const LabledVector& vector);
        LabledVector(LabledVector&& vector);

        LabledVector& operator=(const LabledVector& vector);
        LabledVector& operator=(LabledVector&& vector);        
    };

    
} // namespace patrick

#endif