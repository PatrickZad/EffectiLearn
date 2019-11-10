#include "mlp.h"
#include <cmath>
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
    std::vector<LabledVector> datas;
    for (unsigned long i = 0; i < length; i++)
    {
        LabledVector vec=LabledVector{data+i*width, width, *(lable+i)};
        vec.append(-1);
        datas.push_back(vec);
    }
    double preCost=-1;//this make sure that if the first turn's cost is alredy small , training won't break immediately 
    for (int t = 0; t < maxRepeat; t++)
    {
        std::vector<Matrix> paramGradient{network.size()};//accumulated gradients
        double currentCost=0;
        for (unsigned long i = 0; i < datas.size(); i++)
        {
            std::vector<Vector> layerInputs;//element j is input to layer j
            layerInputs.push_back(datas[i]);
            Vector output=network[0].output(layerInputs[0]);
            for (unsigned long j = 1; j < network.size(); i++)
            {
                output.append(-1);
                layerInputs.push_back(output);
                output=network[j].output(layerInputs[j]);
            }//output is the final output when ends
            currentCost+=cost.cost(datas[i], output);
            //calculate accumulated gradient matrices
            Vector costToOutputGradient=cost.derivative(output);
            unsigned long layerIndex=network.size()-1;
            for (; layerIndex >=0; layerIndex--)
            {
                Matrix outputToWeightsGradient=network[layerIndex].derivativeParemeter(layerInputs[layerIndex]);
                if (paramGradient[layerIndex].getLength()==0)
                {
                    paramGradient[layerIndex]=wideMultiply(costToOutputGradient, outputToWeightsGradient);
                }else
                {
                    //accumulated
                    paramGradient[layerIndex]+=wideMultiply(costToOutputGradient, outputToWeightsGradient);
                }
                //update cost to output gradient
                Matrix matGradient=network[layerIndex].derivativeInput(layerInputs[layerIndex])*Matrix{costToOutputGradient};
                costToOutputGradient=matGradient.getColumns()[0];
            }
        }
        //update network weights
        for (unsigned long i = 0; i < network.size(); i++)
        {
            const Matrix& preWeights=network[i].getWeights();
            Matrix newWeights=preWeights-rate*paramGradient[i];
            network[i].updateWeights(newWeights);
        }
        if (std::abs(currentCost-preCost)<minChange)
        {
            break;
        }
        preCost=currentCost;
    }
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