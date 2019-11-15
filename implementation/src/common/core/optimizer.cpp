#include "optimizer.h"
#include <cmath>
//using namespace patrick;
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
/*
template<class T>
T TargetFunction<T>::GradientDescent(T& init, double rate, double minVariation,unsigned int maxReapt)
{
    T minimumPoint=init;
    double previous=(*this)(minimumPoint);
    for (unsigned int i = 0; i < maxReapt; i++)
    {
        T newInput=minimumPoint-derivative(minimumPoint)*rate;
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