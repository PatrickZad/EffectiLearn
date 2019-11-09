#ifndef CORE_NEURON_H
#define CORE_NEURON_H
#include "./../../common/core/Vector.h"
#include "./../../common/core/Vector.h"
namespace patrick
{
    class ActivationFunc
    {
    //linear as default
    public:
        virtual Vector operator()(Vector& input)=0;
        virtual Vector derivative(Vector& input)=0;
    };
    class Linear : public ActivationFunc
    {
    public:
        Vector operator()(Vector& input);
        Vector derivative(Vector& input);
    };
    class Sigmoid : public ActivationFunc
    {
    public:
        Vector operator()(Vector& input);
        Vector derivative(Vector& input);
    };
    class Softmax : public ActivationFunc
    {
    public:
        Vector operator()(Vector& input);
        Vector derivative(Vector& input);
    };
    class ReLU : public ActivationFunc
    {
    public:
        Vector operator()(Vector& input);
        Vector derivative(Vector& input);
    };
    class TanH : public ActivationFunc
    {
    public:
        Vector operator()(Vector& input);
        Vector derivative(Vector& input);
    };
} // namespace patrick

#endif