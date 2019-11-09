#include "layer.h"
#include <cstdlib>
#include <ctime>
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

Matrix Layer::derivativeInput(Vector& input)
{
    Vector expand=input;
    expand.append(-1);
    std::vector<Vector> columns=weights.getColumns();
    Vector product{width};
    for (unsigned long i = 0; i < width; i++)
    {
        product[i]=columns[i]*expand;
    }
    Vector gradientActi=activation.derivative(product);
    return wideMultiply(gradientActi, weights);
}

Matrix Layer::derivativeParemeter(Vector& input)
{
    Vector expand=input;
    expand.append(-1);
    std::vector<Vector> columns=weights.getColumns();
    Vector product{width};
    for (unsigned long i = 0; i < width; i++)
    {
        product[i]=columns[i]*expand;
    }
    Vector gradientActi=activation.derivative(product);
    for (unsigned long i = 0; i < width; i++)
    {
        columns[i]=gradientActi[i]*expand;
    }
    return Matrix{columns};
}

void Layer::updateWeights(Matrix& newWeights)
{
    weights=newWeights;
    weightsTrans=newWeights.transposition();
}

const Matrix& Layer::getWeights()
{
    return weights;
}

void Layer::initParemeters()
{
    std::srand(0);
    for (unsigned long i = 0; i < weights.getLength(); i++)
    {
        for (unsigned long j = 0; j < weights.getWidth(); j++)
        {
            weights[i][j]=(rand()%10)/10;
        }
    }
    weightsTrans=weights.transposition();
}