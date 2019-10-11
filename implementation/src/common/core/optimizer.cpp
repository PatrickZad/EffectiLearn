#include "optimizer.h"
#include <cmath>
using namespace patrick;

Vector RapidGradientDescent(TargetFuntion<Vector>& target, double minVariation,unsigned int maxReapt)
{
    unsigned int repeat=0;
    double variation=minVariation+1;
    double previous=target();
    double rate=0.01;
    do
    {
        target.minimum-=target.derivative()*rate;
        variation=target()-previous;
    }while (repeat<maxReapt && std::fabs(variation)>minVariation);
    return target.minimum;
}