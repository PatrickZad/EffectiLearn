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
        Matrix weightsTrans;//include weights and bias, weights of a neuron is a row vector
        Matrix weights;
        ActivationFunc& activation;
        unsigned long width;
    public:
        Layer(ActivationFunc& activation, unsigned long width, unsigned long dataLength);
        Vector output(Vector& input);
        Matrix derivativeInput(Vector& input);
        Matrix derivativeParemeter(Vector& input);
        void updateWeights(Matrix& newWeights);
        const Matrix& getWeights();
    private:
        void initParemeters();
    };
} // namespace patrick

#endif