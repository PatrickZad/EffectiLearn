#include "logistic.h"
#include <map>
#include <cmath>
using namespace patrick;

void Logistic::train(double* data, unsigned long width, unsigned long* lable, unsigned long length)
{
    std::map<unsigned long, std::vector<Vector>> lableDataMap;
    for (unsigned long i = 0; i < length; i++)
    {
        Vector sample{data+i*width, width};
        sample.append(1);
        lableDataMap[*(lable+i)].push_back(sample);
    }
    weights=Matrix{width+1, lableDataMap.size()-1, 0.01};
    LogisticTarget target{lableDataMap};
    weights=target.GradientDescent(weights, 0.1);
}

unsigned long Logistic::classify(double* dataRow,unsigned long width)
{
    unsigned long lable=k-1;
    double value=1;
    for (unsigned long i = 0; i < k-1; i++)
    {
        Vector weightVec{weights[i], width};
        Vector dataVec{dataRow, width};
        double newValue=std::exp(weightVec*dataVec);
        if (newValue>value)
        {
            value=newValue;
            lable=i;
        }
    }
    return lable;
}

inline double denominator(std::vector<Vector>& weights, Vector& sample)
{
    double result=1;
    for (Vector& weight : weights)
    {
        result+=std::exp(weight*sample);
    }
    return result;
}

Matrix LogisticDerivative::operator()(Matrix& weights)
{
    std::vector<Vector> columns=weights.getColumns();
    std::vector<Vector> gradients;
    for (unsigned long i=0; i<columns.size(); i++)
    {
        Vector gradient{columns[0].size()};
        std::map<unsigned long, std::vector<Vector>>::iterator iter=lableDataMap.begin();
        for ( ; iter != lableDataMap.end(); iter++)//different lables and their datas
        {
            for (Vector& sample : iter->second)
            {
                double multi=std::exp(columns[i]*sample)/denominator(columns, sample);
                gradient+=multi*sample;   
            }
        }
        for (Vector& sample : lableDataMap[i])
        {
            gradient-=sample;
        }
        gradients.push_back(gradient);
    }
    return Matrix{gradients};
}

LogisticTarget::~LogisticTarget()
{
    delete &derivative;
}

double LogisticTarget::operator()(Matrix& weights)
{
    double result=0;
    std::vector<Vector> columns=weights.getColumns();
    std::map<unsigned long, std::vector<Vector>>::iterator iter=lableDataMap.begin();
    for ( ; iter != lableDataMap.end(); iter++)
    {
        for (Vector& sample : iter->second)
        {
            result+=denominator(columns, sample); 
        }
    }
    for (unsigned long i = 0; i < columns.size(); i++)
    {
        for (Vector& sample : lableDataMap[i])
        {
            result-=columns[i]*sample;
        }
    }
    return result;
}