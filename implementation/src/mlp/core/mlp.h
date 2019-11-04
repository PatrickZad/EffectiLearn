#ifndef CORE_MLP_H
#define CORE_MLP_H
#include "activation.h"
#include "layer.h"
#include <vector>
#include "./../../common/core/classifier.h"
namespace patrick
{
    class MLP : public Classifier
    {
    private:
        std::vector<Layer> network;
    public:
        MLP(unsigned long depth, unsigned long * widths, ActivationFunc* activations=nullptr);
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        long classify(double* dataRow,unsigned long width);
    };
    
} // namespace patrick

#endif