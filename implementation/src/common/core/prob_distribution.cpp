#include "prob_distribution.h"
#include <cmath>
using namespace patrick;
const double PI=std::atan(1.0)*4.0;
Gaussian::Gaussian(unsigned long dim, Matrix& sigma, Vector& mu)
    : dim{dim}, sigma{sigma}, mu{mu}
{
    double sqrtDet=std::sqrt(sigma.det());
    denominator=std::pow(2*PI, dim/2.0)*sqrtDet;
    inverse=sigma.inverse();
}

double Gaussian::probability(Vector& sample)
{
    Matrix data{sample};
    Matrix diff=data-mu;
    Matrix pow=-0.5*diff.transposition()*inverse*diff;
    return std::exp(pow[0][0])/denominator;
}