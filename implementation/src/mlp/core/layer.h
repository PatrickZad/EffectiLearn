#ifndef CORE_LAYER_H
#define CORE_LAYER_H
#include "./../../common/core/Matrix.h"
#include "activation.h"
#include "./../../common/core/Vector.h"
namespace patrick
{
    class Layer
    {
    private:
        Matrix weights;//include weights and bias
        ActivationFunc activation;
        unsigned long width;
    public:
        Layer(ActivationFunc& activation, unsigned long width);
        Vector output(Vector& input);
        Matrix derivative(Vector& input);
    private:
        void initParemeters();
    };
} // namespace patrick

#endif