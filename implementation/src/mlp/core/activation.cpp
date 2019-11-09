#include "activation.h"
#include <cmath>
using namespace patrick;
Vector Linear::operator()(Vector& input)
{
    Vector result=input;
    return result;
}

Vector Linear::derivative(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < result.size(); i++)
    {
        result[i]=1;
    }
    return result;
}

Vector Sigmoid::operator()(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=1/(1+std::exp(-1*input[i]));
    }
    return result;
}

Vector derivative(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        double value=1/(1+std::exp(-1*input[i]));
        result[i]=value*(1-value);
    }
    return result;
}

Vector Softmax::operator()(Vector& input)
{
    Vector result{input.size()};
    double sum=0;
    for (unsigned long i = 0; i < input.size(); i++)
    {
        double exp=std::exp(input[i]);
        result[i]=exp;
        sum+=exp;
    }
    return (1/sum)*result;
}

Vector Softmax::derivative(Vector& input)
{
    double sum=0;
    for (unsigned long i = 0; i < input.size(); i++)
    {
        sum+=std::exp(input[i]);
    }
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=(sum-std::exp(input[i]))/sum*input[i];
    }
    return result;
}

Vector ReLU::operator()(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=std::max(0.0, input[i]);
    }
    return result;
}

Vector ReLU::derivative(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=input[i]>0 ? 1 : 0 ;
    }
    return result;
}

Vector TanH::operator()(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=std::tanh(input[i]);
    }
    return result;
}

Vector TanH::derivative(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=1-std::pow(std::tanh(input[i]),2);
    }
    return result;
}
