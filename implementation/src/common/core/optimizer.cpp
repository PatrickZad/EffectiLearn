#include "optimizer.h"
#include <cmath>
using namespace patrick;
/*
template<class T>
T TargetFunction<T>::RapidGradientDescent(T& init, double minVariation=0.001,unsigned int maxReapt=200)
{
    T minimumPoint=init;
    double previous=(*this)(minimumPoint);
    for (unsigned int i = 0; i < maxReapt; i++)
    {
        RateTarget<T> rateTarget{*this, minimumPoint};
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
*/
template<class T>
T TargetFunction<T>::GradientDescent(T& init, double rate, double minVariation=0.001,unsigned int maxReapt=200)
{
    T minimumPoint=init;
    double previous=(*this)(minimumPoint);
    for (unsigned int i = 0; i < maxReapt; i++)
    {
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

template<class T>
double RateTargetDerivative<T>::operator()(double& rate)
{
    T originGradient=originDerivative(originInput);
    T newInput=originInput-originGradient*rate;
    return originDerivative(newInput)*(originGradient*(-1));
}

template<class T>
RateTarget<T>::~RateTarget()
{
    delete &(this->derivative);
}

template<class T>
double RateTarget<T>::operator()(double& input)
{
    T newInput=originInput-originTarget.derivative(originInput)*input;
    return originTarget(newInput);
}

template<class T>
double RateTarget<T>::searchRate(double minVariation, unsigned int maxReapt)
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
 