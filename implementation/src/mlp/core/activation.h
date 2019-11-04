#ifndef CORE_NEURON_H
#define CORE_NEURON_H
#include "./../../common/core/Vector.h"
namespace patrick
{
    class ActivationFunc
    {
    //linear as default
    public:
        double operator()(Vector& input);
    };
    class Sigmoid : public ActivationFunc
    {
    public:
        double operator()(Vector& input);
    };
    class Softmax : public ActivationFunc
    {
    public:
        double operator()(Vector& input);
    };
    class ReLU : public ActivationFunc
    {
    public:
        double operator()(Vector& input);
    };
    class TanH : public ActivationFunc
    {
    public:
        double operator()(Vector& input);
    };
} // namespace patrick

#endif