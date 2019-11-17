#ifndef CORE_MLP_H
#define CORE_MLP_H
#include "activation.h"
#include "layer.h"
#include <vector>
#include "cost.h"
#include "layer.h"
#include "./../../common/core/classifier.h"
namespace patrick
{
    class MLP : public Classifier
    {
    private:
        std::vector<Layer> network;
        CostFunc& cost;
        int maxRepeat=500;
        double minChange=0.001;
        double rate=0.01;
    public:
    //input layer not need to be included, output layer included
        MLP(std::vector<Layer> layers, CostFunc& cost) : network{layers}, cost{cost} {};
        void train(double* data, unsigned long width,unsigned long* lable, unsigned long length);
        unsigned long classify(double* dataRow,unsigned long width);
        Vector output(double* data, unsigned long width);
    };
    
} // namespace patrick

#endif