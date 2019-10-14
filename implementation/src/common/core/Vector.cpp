#include "Vector.h"
#include "exception/exception.h"
using namespace patrick;
Vector::Vector(double* row, unsigned long length)
{
    array=new double[length];
    for (long i = 0; i < length; i++)
    {
        array[i]=row[i];
    }
    this->length=length;
}

Vector::Vector(unsigned long length, double init)
{
    array=new double[length];
    for (long i = 0; i < length; i++)
    {
        array[i]=init;
    }
    this->length=length;
}

Vector::Vector(const Vector& vector)
{
    array=new double[vector.length];
    for (long i = 0; i < vector.length; i++)
    {
        array[i]=(vector.array)[i];
    }
    this->length=vector.length;
}
Vector::Vector(Vector&& vector)
{
    this->array=vector.array;
    this->length=vector.length;
    vector.array=nullptr;
    vector.length=0;
}

Vector::~Vector(){
    delete[] array;
    length=0;
}

Vector& Vector::operator=(const Vector& vector)
{
    delete[] array;
    array=new double[vector.length];
    for (long i = 0; i < vector.length; i++)
    {
        array[i]=(vector.array)[i];
    }
    this->length=vector.length;
}
Vector& Vector::operator=(Vector&& vector)
{
    delete[] this->array;
    this->array=vector.array;
    this->length=vector.length;
    vector.array=nullptr;
    vector.length=0;
}

Vector& Vector::operator+=(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    for (long i = 0; i < this->length; i++)
    {
        this->array[i]+=vector.array[i];
    }
    return *this;
}

Vector& Vector::operator-=(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    for (long i = 0; i < this->length; i++)
    {
        this->array[i]-=vector.array[i];
    }
    return *this;
}

double& Vector::operator[](unsigned long index)const
{
    if (this->length<=index)
    {
        throw OutOfIndexException{};
    }
    return this->array[index];
}


long Vector::size()const
{
    return length;
}

Vector& Vector::concat(const Vector& vec)
{
    double * array=new double[this->length+vec.length];
    for (unsigned long i = 0; i < this->length; i++)
    {
        *(array+i)=*(this->array+i);
    }
    for (unsigned long i = 0; i < vec.length; i++)
    {
        *(array+this->length+i)=*(vec.array+i);
    }
    delete this->array;
    this->array=array;
    this->length=this->length+vec.length;
    return *this;
}

//operator reload

double patrick::operator*(const Vector& v1, const Vector& v2)
{
    if (v1.size() != v2.size())
    {
        throw CalculationNotValidException{};
    }
    double sum=0;
    for (long i = 0; i < v1.size(); i++)
    {
        sum+=v1[i]*v2[i];
    }
    return sum;
}

Vector patrick::operator*(const Vector& v, double num)
{
    double sum[v.size()];
    for (long i = 0; i < v.size(); i++){
        sum[i]=v[i]*num;
    }    
    return Vector{sum,v.size()};
}

Vector patrick::operator*(double num, const Vector& v)
{
    return v*num;
}

Vector patrick::operator+(const Vector& v1, const Vector& v2)
{
    if (v1.size() != v2.size())
    {
        throw CalculationNotValidException{};
    }
    double sum[v1.size()];
    for (long i = 0; i < v1.size(); i++){
        sum[i]=v1[i]+v2[i];
    }    
    return Vector{sum,v1.size()};
}


Vector patrick::operator-(const Vector& v1, const Vector& v2)
{
    if (v1.size() != v2.size())
    {
        throw CalculationNotValidException{};
    }
    double diff[v1.size()];
    for (long i = 0; i < v1.size(); i++){
        diff[i]=v1[i]-v2[i];
    }    
    return Vector{diff,v1.size()};
}


