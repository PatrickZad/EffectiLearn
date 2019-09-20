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
        throw 
    }
    
}
Vector& Vector::operator+=(const Vector& vector)
{}
Vector Vector::operator*(const Vector& vector)
{}
Vector Vector::operator-(const Vector& vector)
{}
Vector& Vector::operator-=(const Vector& vector)
{}
double Vector::operator[](unsigned int index)
{}