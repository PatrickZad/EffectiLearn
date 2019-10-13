#include "logistic.h"
#include <map>
#include <cmath>
using namespace patrick;

void Logistic::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    //initialize weights, map and targets
    std::map<unsigned long, std::vector<Vector>> lableDataMap;
    std::vector<LogisticTarget> targets;
    unsigned long i = 0;
    for (; i < weights.size(); i++)
    {
        weights[i]=Vector{width+1,0.1};
        lableDataMap[i]=std::vector<Vector>{};
        targets.push_back(LogisticTarget{weights,i});
    }
    lableDataMap[i]=std::vector<Vector>{};
    //build map
    Vector expand{1,1};
    for(i=0 ; i<length; i++)
    {
        Vector dataVec{data+i*width,width};
        lableDataMap[*(lable+i)].push_back(dataVec.concat(expand));
    }
    double previous=targets[0](weights[0]);
    for (int t = 0;  t< 200; t++)
    {
        std::vector<Vector> newWeights;
        for ( i = 0; i < targets.size(); i++)
        {
            newWeights.push_back(targets[i].RapidGradientDescent(weights[i]));
        }
        weights=newWeights;
        double newValue=targets[0](weights[0]);
        if (std::fabs(newValue-previous)<0.001)
        {
            break;
        }
        previous=newValue;
    }
}

long classify(double* dataRow,unsigned long width)
{
    
}
