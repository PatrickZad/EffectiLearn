#ifndef CORE_MLP_H
#define CORE_MLP_H
#include "activation.h"
#include "layer.h"
#include <vector>
#include "cost.h"
#include "layer.h"
namespace patrick
{
    class MLP 
    {
    private:
        std::vector<Layer> network;
        CostFunc& cost;
        int maxRepeat=200;
        double minChange=0.001;
        double rate=0.1;
    public:
        MLP(unsigned long dataWidth, unsigned long depth, unsigned long * widths, ActivationFunc* activations, CostFunc& cost);
        MLP(std::vector<Layer> layers, CostFunc& cost) : network{layers}, cost{cost} {};
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        Vector output(double* data, unsigned long width);
    };
    
} // namespace patrick

#endif