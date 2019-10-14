#ifndef CORE_COMMON_OPTIMIZER_H
#define CORE_COMMON_OPTIMIZER_H
#include "common.h"
#include "Vector.h"
#include <vector>
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
        T RapidGradientDescent(T& init, double minVariation=0.001,unsigned int maxReapt=200);
    };
    class RateTargetDerivative : public FirstOrderDerivative<double>
    {
    private:
       FirstOrderDerivative<Vector>& originDerivative;
       Vector originInput;
    public:
        RateTargetDerivative(FirstOrderDerivative<Vector>& originDerivative, Vector& originInput)
            :originDerivative{originDerivative},originInput{originInput}{};
        double operator()(double& input);
    };
    
    class RateTarget : public TargetFunction<double>
    {
    private:
        TargetFunction<Vector>& originTarget;
        Vector& originInput;

    public:
        RateTarget(TargetFunction<Vector>& originTarget, Vector& originInput)
            :TargetFunction{*(new RateTargetDerivative{originTarget.derivative,originInput})}, 
                originTarget{originTarget} ,originInput{originInput}{};
        ~RateTarget();
        double operator()(double& input);
        double searchRate(double minVariation=0.001, unsigned int maxReapt=200);//one-dimention search
    };
    
} // namespace patrick
#endif