#ifndef CORE_COMMON_OPTIMIZER_H
#define CORE_COMMON_OPTIMIZER_H
#include "Vector.h"
#include <vector>
#include <cmath>
namespace patrick
{
    template<class T>
    class FirstOrderDerivative
    {
    public:
        virtual T operator()(T& input)=0;
    };

    template<class T>
    class TargetFunction
    {
    public:
        FirstOrderDerivative<T>& derivative;
    public:
        TargetFunction(FirstOrderDerivative<T>& derivative):derivative{derivative}{};//initial value of target
        virtual double operator()(T& input)=0;//tarin data
        //T RapidGradientDescent(T& init, double minVariation=0.001,unsigned int maxReapt=200);
        T GradientDescent(T& init, double rate, double minVariation=0.001,unsigned int maxRepeat=500);
    };
    
} // namespace patrick
using namespace patrick;
template<class T>
T TargetFunction<T>::GradientDescent(T& init, double rate, double minVariation,unsigned int maxReapt)
{
    T minimumPoint=init;
    double previous=(*this)(minimumPoint);
    for (unsigned int i = 0; i < maxReapt; i++)
    {
        T newInput=minimumPoint-derivative(minimumPoint)*rate;
        double newValue=(*this)(newInput);
        if (std::fabs(newValue-previous)<minVariation)
        {
            break;
        }
        previous=newValue;
        minimumPoint=newInput;
    }
    return minimumPoint;
}
#endif