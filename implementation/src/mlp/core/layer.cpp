#include "layer.h"
using namespace patrick;
Layer::Layer(ActivationFunc& activation, unsigned long width, unsigned long dataLength)
    : weights{dataLength+1, width}, activation{activation}, width{width}
{
    initParemeters();
}

Vector Layer::output(Vector& input)
{
    Vector bias{1};
    bias[0]=-1;
    Vector product=(weightsTrans*Matrix{input.concat(bias)}).getColumns()[0];
    return activation(product);
}

Matrix Layer::derivative(Vector& input)
{

}

void Layer::initParemeters()
{
    
}