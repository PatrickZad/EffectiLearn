#ifndef CORE_COMMON_OPTIMIZER_H
#define CORE_COMMON_OPTIMIZER_H
#include "common.h"
#include <vector>
namespace patrick
{
    template<class T>
    class TargetFuntion
    {
    public:
        T minimum;//target of optimizer
        FirstOrderDerivative derivative;
    public:
        TargetFuntion(T& init, FirstOrderDerivative& derivative):minimum{init}{};//initial value of target
        virtual double operator()()=0;//tarin data
    };

    class FirstOrderDerivative
    {
    public:
        Vector operator()(std::vector<Vector>& train);
    };
    
    class RapidGradientDescentRateTarget:TargetFuntion<double>
    {
    private:
        /* data */
    public:
        using TargetFuntion::TargetFuntion;
        double operator()();
    };
    
    double oneDimSearch(TargetFuntion<double>& target);
    Vector RapidGradientDescent(TargetFuntion<Vector>& target, double minVariation=0.001,unsigned int maxReapt=200);
    
} // namespace patrick

#endif