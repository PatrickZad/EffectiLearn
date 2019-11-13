#include "dist_func.h"
#include "./../../exception/exception.h"
#include <cmath>
using namespace patrick;
MinkowskiDist::MinkowskiDist(unsigned long pow)
{
    if (pow < 1)
    {
        throw ParameterInvalidException{};
    }
}

double MinkowskiDist::operator()(Vector& vec0, Vector& vec1)
{
    if (vec0.size() != vec1.size())
    {
        throw ParameterInvalidException{};
    }
    double sum=0;
    for (unsigned long i = 0; i < vec0.size(); i++)
    {
        sum+=std::pow(std::abs(vec0[i]-vec1[i]),pow);
    }
    return std::pow(sum, 1.0/pow);
}