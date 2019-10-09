#include "common.h"
#include <initializer_list>
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

Vector::Vector(unsigned long length, double init){
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
Vector Vector::operator+(const Vector& vector)
{
    if (this->length!=vector.length)
    {
        throw CalculationNotValidException{};
    }
    double sum[this->length];
    for (long i = 0; i < this->length; i++){
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
    for (long i = 0; i < this->length; i++)
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
    for (long i = 0; i < this->length; i++)
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
    for (long i = 0; i < this->length; i++){
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
    for (long i = 0; i < this->length; i++)
    {
        this->array[i]-=vector.array[i];
    }
    return *this;
}
double& Vector::operator[](unsigned long index)
{
    if (this->length<=index)
    {
        throw OutOfIndexException{};
    }
    return this->array[index];
}

long Vector::size()
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