#ifndef COMMON_CORE_VECTOR_H
#define COMMON_CORE_VECTOR_H
namespace patrick
{
    class Vector
    {
    private:
        double* array=nullptr;
        long length=0;
    public:
        Vector();
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
        
        long size()const;
        Vector& concat(const Vector& vec);
    };
    double operator*(const Vector& v1,const  Vector& v2);
    Vector operator*(const Vector& v,double num);
    Vector operator*(double num, const Vector& v);
    Vector operator+(const Vector& v1, const Vector& v2);
    Vector operator-(const Vector& v1, const Vector& v2);
} // namespace patrick

#endif