#include "common.h"
#include <initializer_list>
#include "exception/exception.h"
using namespace patrick;
Vector::Vector(double* row, unsigned int length)
{
    array=new double[length];
    for (unsigned int i = 0; i < length; i++)
    {
        array[i]=row[i];
    }
    this->length=length;
}

Vector::Vector(const Vector& vector)
{
    array=new double[vector.length];
    for (unsigned int i = 0; i < vector.length; i++)
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
    for (unsigned int i = 0; i < vector.length; i++)
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
Vector Vector::operator+(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    double sum[this->length];
    for (unsigned int i = 0; i < this->length; i++){
        sum[i]=this->array[i]+vector.array[i];
    }    
    return Vector{sum,this->length};
}
Vector& Vector::operator+=(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    for (unsigned int i = 0; i < this->length; i++)
    {
        this->array[i]+=vector.array[i];
    }
    return *this;
}
double Vector::operator*(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    double sum=0;
    for (unsigned int i = 0; i < this->length; i++)
    {
        sum+=(*this)[i]*vector.array[i];
    }
    return sum;
}
Vector Vector::operator-(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    double diff[this->length];
    for (unsigned int i = 0; i < this->length; i++){
        diff[i]=this->array[i]-vector.array[i];
    }    
    return Vector{diff,this->length};
}
Vector& Vector::operator-=(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    for (unsigned int i = 0; i < this->length; i++)
    {
        this->array[i]-=vector.array[i];
    }
    return *this;
}
double& Vector::operator[](unsigned int index)
{
    if (this->length<=index)
    {
        throw OutOfIndexException{};
    }
    return this->array[index];
}