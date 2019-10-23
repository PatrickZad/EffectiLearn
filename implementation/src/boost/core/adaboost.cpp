#include "adaboost.h"
#include <cmath>
#include <map>
using namespace patrick;
void AdaBoost::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    std::vector<double> dataweights;
    //initialize dataweights
    for (unsigned long i = 0; i < length; i++)
    {
        dataweights.push_back(1/length);
    }
    //train classifiers, calculate weights
    for (unsigned long i = 0; i < classifiers.size(); i++)
    {
        classifiers[i].train(data, width, lable, length);
        double error=0;
        std::vector<long> classifys;
        for (unsigned long j = 0; j < length; j++)
        {
            classifys.push_back(classifiers[i].classify(data+i*width, width));
            if (*(lable+j) != classifys[j])
            {
                error+=dataweights[j];
            }
        }
        weights.push_back(0.5*std::log((1-error)/error));
        double formalizer=0;
        for (unsigned long j = 0; j < length; j++)
        {
            dataweights[j]*=std::exp((-1)*weights[i]*(*(lable+j))*classifys[j]);
            formalizer+=dataweights[j];
        }
        for (unsigned long j = 0; j < length; j++)
        {
            dataweights[j]/=formalizer;
        }
    }
}
long AdaBoost::classify(double* dataRow,unsigned long width)
{
    std::map<long,double> votes;
    for (unsigned long i = 0; i < classifiers.size(); i++)
    {
        long lable=classifiers[i].classify(dataRow, width);
        if (votes.count(lable)==0)
        {
            votes[lable]=weights[i];
        }else
        {
            votes[lable]+=weights[i];
        }
    }
    std::map<long, double>::iterator iter=votes.begin();
    long lable=iter->first;
    double vote=iter->second;
    for ( iter++; iter != votes.end(); iter++)
    {
        if (iter->second>vote)
        {
            lable=iter->first;
            vote=iter->second;
        }
    }
    return lable;
}