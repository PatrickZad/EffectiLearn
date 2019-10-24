#include "kernel_function.h"
#include <cmath>
using namespace patrick;

double PolynomialKernel::operator()(Vector& vec0, Vector& vec1)
{
    return std::pow(vec0*vec1+1, pow);
}

double GaussianKernel::operator()(Vector& vec0, Vector& vec1)
{
    double index = (-1)*(vec0-vec1)*(vec0-vec1)*0.5*sigma_square;
    return std::exp(index);
}