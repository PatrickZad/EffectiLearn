#include "activation.h"
#include <cmath>
using namespace patrick;
Vector Linear::operator()(Vector& input)
{
    Vector result=input;
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

Vector ReLU::operator()(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=std::max(0.0, input[i]);
    }
    return result;
}

Vector Sigmoid::operator()(Vector& input)
{
    Vector result{input.size()};
    for (unsigned long i = 0; i < input.size(); i++)
    {
        result[i]=std::tanh(input[i]);
    }
    return result;
}