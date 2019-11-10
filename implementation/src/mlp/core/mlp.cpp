#include "mlp.h"
using namespace patrick;
MLP::MLP(unsigned long dataWidth, unsigned long depth, unsigned long * widths, ActivationFunc* activations, CostFunc& cost)
    :cost{cost}
{
    Layer first{*activations, *widths, dataWidth};
    network.push_back(first);
    for (unsigned long i = 1; i < depth; i++)
    {
        Layer layer{*(activations+i), *(widths+i), *(widths+i-1)};
        network.push_back(layer);
    }
}

void MLP::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    
}

Vector MLP::output(double* data, unsigned long width)
{
    Vector dataVec{data, width};
    dataVec.append(-1);
    for (unsigned long i = 0; i < network.size(); i++)
    {
        dataVec=network[i].output(dataVec);
    }
    return dataVec;
}