#include "optimizer.h"
#include <cmath>
using namespace patrick;

template<class T>
T TargetFunction<T>::RapidGradientDescent(T& init, double minVariation=0.001,unsigned int maxReapt=200)
{
    T minimumPoint=init;
    double previous=(*this)(minimumPoint);
    for (unsigned int i = 0; i < maxReapt; i++)
    {
        RateTarget rateTarget{*this, minimumPoint};
        double rate=rateTarget.searchRate();
        T newInput=minimum-derivative(minimumPoint)*rate;
        double newValue=*(this)(newInput);
        if (std::fabs(newValue-previous)<minVariation)
        {
            break;
        }
        previous=newValue;
        minimumPoint=newInput;
    }
    return minimumPoint;
}

double RateTargetDerivative::operator()(double& rate)
{
    Vector originGradient=originDerivative(originInput);
    Vector newInput=originInput-originGradient*rate;
    return originDerivative(newInput)*(originGradient*(-1));
}

RateTarget::~RateTarget()
{
    delete &(this->derivative);
}

double RateTarget::operator()(double& input)
{
    Vector newInput=originInput-originTarget.derivative(originInput)*input;
    return originTarget(newInput);
}

double RateTarget::searchRate(double minVariation, unsigned int maxReapt)
{
    double rateBeforeLast=minVariation*10;
    double rateLast=minVariation*20;
    double rate;
    unsigned int repeat=0;
    if ((*this)(rateBeforeLast)<(*this)(rateLast))
    {
        rateBeforeLast=minVariation*20;
        rateLast=minVariation*10;
    }
    for (unsigned int i = 0; i < maxReapt; i++)
    {
        double derivativeLast=derivative(rateLast);
        double derivativeBeforeLast=derivative(rateBeforeLast);
        rate = (derivativeLast*rateBeforeLast-derivativeBeforeLast*rateLast
            )/(derivativeLast-derivativeBeforeLast);
        if (std::fabs(rate-rateLast)<minVariation)
        {
            break;
        }
        rateBeforeLast=rateLast;
        rateLast=rate;
    }
    return rate;
}
