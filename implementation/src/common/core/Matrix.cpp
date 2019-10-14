#include "Matrix.h"
#include "exception/exception.h"
using namespace patrick;

Matrix::Matrix(unsigned long  length, unsigned long width, double init)
    :width{width}, length{length}, start{new double[width*length]}
{
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            *(start+i*width+j)=init;
        }
    }
    
}

Matrix::Matrix(Vector& vec, short shape=VECTOR_COLUMN)
{
    start=new double[vec.size()];
    for (unsigned long i = 0; i < vec.size(); i++)
    {
        *(start+i)=vec[i];
    }
    switch(shape)
    {
        case VECTOR_COLUMN:
            width=1;
            length=vec.size();
            break;
        case VECTOR_ROW:
            width=vec.size();
            length=1;
            break;
        default:
            throw ParameterInvalidException{};
    }
}

Matrix::~Matrix()
{
    delete[] start;
}