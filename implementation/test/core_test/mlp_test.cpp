#include "common.h"
#include "./../../src/mlp/core/mlp.h"
#include "./../../src/mlp/core/activation.h"
#include "./../../src/mlp/core/cost.h"
int main()
{
    using namespace patrick;
    DataPtr data=readData(IRIS);
    unsigned long layerWidth[6]={8,9,6,10,6,3};
    std::vector<Layer> layers;
    int i=1;
    Linear linearActivation{};
    Sigmoid sigActivation{};
    Softmax softmaxActivation{};
    Layer first{linearActivation, layerWidth[0], 4};
    layers.push_back(first);
    for (; i < 3; i++)
    {
        Layer layer{linearActivation, layerWidth[i], layerWidth[i-1]};
        layers.push_back(layer);
    }
    for (; i < 5; i++)
    {
        Layer layer{sigActivation, layerWidth[i], layerWidth[i-1]};
        layers.push_back(layer);
    }
    Layer layer{softmaxActivation, layerWidth[i], layerWidth[i-1]};
    layers.push_back(layer);
    CrossEntropy cost{};
    MLP nn{layers, cost};
    nn.train(data.data, data.width, data.lable, data.length);
    nn.test(data.data, data.width, data.lable, data.length);
    return 0;
}