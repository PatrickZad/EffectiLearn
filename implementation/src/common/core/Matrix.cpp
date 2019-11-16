#include "./../../exception/exception.h"
#include "Matrix.h"
#include "util.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace patrick;

Matrix::Matrix(unsigned long squareWidth)
    :width{squareWidth}, length{squareWidth}, start{new double[squareWidth*squareWidth]}
{
    for (unsigned long i = 0; i < squareWidth; i++)
    {
        *(start+squareWidth*i+i)=1;
    }
}

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

Matrix::Matrix(Vector& vec, short shape): start{new double[vec.size()]}
{
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

Matrix::Matrix(std::vector<Vector>& vects, short shape)
{
    if (vects.size()==0){
        return ;
    }
    start=new double[vects.size()*vects[0].size()];
    if (shape==VECTOR_COLUMN)
    {
        length=vects[0].size();
        width=vects.size();
        for (unsigned long i=0; i<length; i++){
            for (unsigned long j=0; j<width; j++){
                *(start+i*width+j)=vects[j][i];
            }
        }
    } else{
        width=vects[0].size();
        length=vects.size();
        for (unsigned long i=0; i<length; i++){
            for (unsigned long j=0; j<width; j++){
                *(start+i*width+j)=vects[i][j];
            }
        }
    }
}

Matrix::Matrix(const Matrix& m)
    : width{m.width}, length{m.length}, start{new double[m.width*m.length]}
{
    for (unsigned long i = 0; i < m.length; i++)
    {
        for (unsigned long j = 0; j < m.width; j++)
        {
            (*this)[i][j]=m[i][j];
        }
    }
}

Matrix::Matrix(Matrix&& m) : width{m.width}, length{m.length}, start{m.start}
{
    m.start=nullptr;
    m.width=0;
    m.length=0;
}

Matrix::~Matrix()
{
    delete[] start;
    width=0;
    length=0;
    start=nullptr;
}

unsigned long Matrix::getLength()const
{
    return length;
}

unsigned long Matrix::getWidth()const
{
    return width;
}

Matrix& Matrix::operator=(const Matrix& m)
{
    delete[] start;
    start=new double[m.length*m.width];
    length=m.length;
    width=m.width;
    for (unsigned long i = 0; i < m.length; i++)
    {
        for (unsigned long j = 0; j < m.width; j++)
        {
            (*this)[i][j]=m[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator=(Matrix&& m)
{
    delete[] start;
    start=m.start;
    length=m.length;
    width=m.width;
    m.start=nullptr;
    m.width=0;
    m.length=0;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
    if(m.length!=length || m.width !=width)
    {
        throw CalculationInvalidException{};
    }
    for (unsigned long i = 0; i < m.length; i++)
    {
        for (unsigned long j = 0; j < m.width; j++)
        {
            (*this)[i][j]+=m[i][j];
        }
    }
    return *this;
}

double* Matrix::operator[](unsigned long index)const
{
    return start+index*width;
}

Matrix Matrix::transposition()
{
    Matrix result{width,length};
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            result[j][i]=(*this)[i][j];
        }
    }
    return result;
}

inline double innerProduct(double* row, unsigned long width, double* column, unsigned long interval)
{
    double sum=0;
    for (unsigned long i = 0; i < width; i++)
    {
        sum+=(*(row+i)) * (*(column+i*interval));
    }
    return sum;
}
/*
Matrix Matrix::inverse()
{
    if ((width!=length) || (this->det()==0))
    {
        throw CalculationInvalidException{};
    }
    return this->adjugate()*(1/this->det());
}

double Matrix::det()
{
    if (width!=length)
    {
        throw CalculationInvalidException{};
    }
    
    std::vector<unsigned long> columns;
    for (unsigned long i = 0; i < width; i++)
    {
        columns.push_back(i);
    }
    std::vector<std::vector<unsigned long>> permutations;
    permutations=allPermutation(columns);
    std::vector<std::vector<unsigned long>>::iterator iter=permutations.begin();
    double result=0;
    for (; iter!=permutations.end(); iter++)
    {
        double product=std::pow(-1, patrick::inversionNum(*iter));
        for (unsigned long i = 0; i < iter->size(); i++)
        {
            product*=(*this)[i][(*iter)[i]];
        }
        result+=product;
    }
    return result;
}

inline Matrix subMatrix(Matrix& origin, unsigned long row, unsigned long column)
{
    Matrix sub{origin.getLength()-1, origin.getWidth()-1};
    for (unsigned long r = 0; r < row; r++)
    {
        for (unsigned long c = 0; c < column; c++)
        {
            sub[r][c]=origin[r][c];
        }
        for (unsigned long c = column+1; c < origin.getWidth(); c++)
        {
            sub[r][c-1]=origin[r][c];
        }
    }
    for (unsigned long r = row+1; r < origin.getLength(); r++)
    {
        for (unsigned long c = 0; c < column; c++)
        {
            sub[r-1][c]=origin[r][c];
        }
        for (unsigned long c = column+1; c < origin.getWidth(); c++)
        {
            sub[r-1][c-1]=origin[r][c];
        }
    }
    return sub;
}

Matrix Matrix::adjugate()
{
    if ((width!=length) || (this->det()==0))
    {
        throw CalculationInvalidException{};
    }   
    Matrix adjugate{width, length};
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            adjugate[i][j]=subMatrix(*this, i, j).det();
        }
    }
    return adjugate;
}
*/
std::vector<Vector> Matrix::getRows()
{
    std::vector<Vector> result;
    for (unsigned long i = 0; i < length; i++)
    {
        result.push_back(Vector{start+i*width, width});
    }
    return result;
}
std::vector<Vector> Matrix::getColumns()
{
    std::vector<Vector> result;
    for (unsigned long i = 0; i < width; i++)
    {
        Vector column{length};
        for (unsigned long j = 0; j < length; j++)
        {
            column[j]=(*this)[j][i];
        }
        result.push_back(column);
    }
    return result;
}

Matrix patrick::operator*(const Matrix& m1, const Matrix& m2)
{
    if (m1.getWidth()!=m2.getLength())
    {
        throw CalculationInvalidException{};
    }
    Matrix result{m1.getLength(),m2.getWidth()};
    for (unsigned long i = 0; i < result.getLength(); i++)
    {
        for (unsigned long j = 0; j < result.getWidth(); j++)
        {
            result[i][j]=innerProduct(m1[i], m1.getWidth(), m2[0]+j, m2.getWidth());
        }
    }
    return result;
}

Matrix patrick::operator*(const Matrix& m, double num)
{
    Matrix result{m.getLength(),m.getWidth()};
    for (unsigned long i = 0; i < result.getLength(); i++)
    {
        for (unsigned long j = 0; j < result.getWidth(); j++)
        {
            result[i][j]=m[i][j]*num;
        }
    }
    return result;
}

Matrix patrick::operator*(double num, const Matrix& m)
{
    return m*num;
}

Matrix patrick::operator+(const Matrix& m1, const Matrix& m2)
{
    if (m1.getLength()!=m2.getLength() || m1.getWidth()!=m2.getWidth())
    {
        throw CalculationInvalidException{};
    }
    Matrix result{m1.getLength(),m1.getWidth()};
    for (unsigned long i = 0; i < result.getLength(); i++)
    {
        for (unsigned long j = 0; j < result.getWidth(); j++)
        {
            result[i][j]=m1[i][j]+m2[i][j];
        }
    }
    return result;
}

Matrix patrick::operator-(const Matrix& m1, const Matrix& m2)
{
    if (m1.getLength()!=m2.getLength() || m1.getWidth()!=m2.getWidth())
    {
        throw CalculationInvalidException{};
    }
    Matrix result{m1.getLength(),m1.getWidth()};
    for (unsigned long i = 0; i < result.getLength(); i++)
    {
        for (unsigned long j = 0; j < result.getWidth(); j++)
        {
            result[i][j]=m1[i][j]-m2[i][j];
        }
    }
    return result;
}

Matrix patrick::operator/(const Matrix& m, double num)
{
    Matrix result{m.getLength(),m.getWidth()};
    for (unsigned long i = 0; i < result.getLength(); i++)
    {
        for (unsigned long j = 0; j < result.getWidth(); j++)
        {
            result[i][j]=m[i][j]/num;
        }
    }
    return result;
}

Matrix patrick::randMatrix(unsigned long length, unsigned long width)
{
    Matrix result{length, width};
    std::srand(0);
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            result[i][j]=(double)(rand()%10)/10;
        }
    }
    return result;
}