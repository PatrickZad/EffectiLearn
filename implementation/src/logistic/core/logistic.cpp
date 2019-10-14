#include "logistic.h"
#include <map>
#include <cmath>
using namespace patrick;

void Logistic::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    std::vector<Matrix> bMatrices{k-1};
    //initialize bMatrices
    for (unsigned long i = 0; i < k-1; i++)
    {
        bMatrices[i]=Matrix{1,k-1};
        bMatrices[i][0][i]=1;
    }
    //initialize weights
    weights=Matrix{k-1,width,0.01};
    //build training data
    std::vector<Vector> datas;
    std::vector<unsigned long> lables;
    for (unsigned long i=0; i < length; i++)
    {
        datas.push_back(Vector{data+width*i,width});
        lables.push_back(*(lable+i));
    }
    LogisticTarget target{bMatrices, datas, lables};
    weights=target.GradientDescent(weights, 0.1);
}

long Logistic::classify(double* dataRow,unsigned long width)
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

Matrix LogisticDerivative::operator()(Matrix& weights)
{
    Matrix result{weights.getLength,weights.getWidth};
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        Matrix part1{};
        if (lables[i]!=weights.getLength())
        {
            part1=bMatrices[lables[i]].transposition()*Matrix{datas[i],VECTOR_ROW};
        }
        else
        {
            part1=Matrix{weights.getLength(),weights.getWidth()};
        }
        
        Matrix numerator{weights.getLength(),weights.getWidth()};
        double denominator=1;
        for (unsigned long j = 0; j < weights.getLength(); j++)
        {
            double exp=std::exp(Vector{weights[j], weights.getWidth()}*datas[i]);
            numerator+=bMatrices[j].transposition()*Matrix{datas[i],VECTOR_ROW}*exp;
            denominator+=exp;
        }
        result+=(part1+numerator/denominator);
    }
    return result;
}

double LogisticTarget::operator()(Matrix& weights)
{
    double result=0;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        double part1=0;
        if (lables[i]!=weights.getLength())
        {
            part1=Vector{weights[lables[i]], weights.getWidth()}*datas[i];
        }
        double part2=1;
        for (unsigned long j = 0; j < weights.getLength(); j++)
        {
            part2+=std::exp(Vector{weights[j], weights.getWidth()}*datas[i]);
        }
        result+=(part1-std::log(part2));
    }
    return result;
}