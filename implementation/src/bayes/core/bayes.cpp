#include "bayes.h"
#include <set>
#include "./../../common/core/Vector.h"
using namespace patrick;

void NaiveBayes::train(double* data, unsigned long width,unsigned long* lable, unsigned long length)
{
    //build lable map
    std::map<unsigned long,unsigned long> lableAmountMap;
    unsigned long index=0;
    for (unsigned long i = 0; i < length; i++)
    {
        if (lableIndexMap.count(*(lable+i))==0)
        {
            lableIndexMap[*(lable+i)]=index;
            index++;
        }
        if (lableAmountMap.count(*(lable+i))==0)
        {
            lableAmountMap[*(lable+i)]=1;
        }
        else
        {
            lableAmountMap[*(lable+i)]++;
        }
    }
    //build attrribute sets
    std::vector<std::set<double>> attrSets{width};
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            attrSets[j].insert((data+i*width)[j]);
        }
    }
    //build attribute map
    conAttrMaps=std::vector<std::map<double,unsigned long>>{width};
    for (unsigned long i = 0; i < width; i++)
    {
        std::set<double>::iterator iter;
        unsigned long index=0;
        for (iter = attrSets[i].begin(); iter != attrSets[i].end(); iter++)
        {
            conAttrMaps[i][*iter]=index;
            index++;
        }
           
    }
    //initialize matrices
    for (unsigned long i = 0; i < width; i++)
    {
        std::vector<std::vector<double>> conMatrix{lableIndexMap.size()};
        for (unsigned long j = 0; j < lableIndexMap.size(); j++)
        {
            conMatrix[j]=std::vector<double> (attrSets[i].size(),0);
        }
        conMatrices.push_back(conMatrix);
    }
    //counting amount
    for (unsigned long i = 0; i < length; i++)
    {
        Vector sample{data+i*width,width};
        for (unsigned long j = 0; j < width; j++)
        {
            unsigned long valueIndex=conAttrMaps[j][sample[j]];
            conMatrices[j][lableIndexMap[*(lable+i)]][valueIndex]++;
        }
    }
    //build lable probability map
    std::map<unsigned long,unsigned long>::iterator mapIter=lableAmountMap.begin();
    for (; mapIter != lableAmountMap.end(); mapIter++)
    {
        lableProbMap[mapIter->first]=(double)((mapIter->second)+1)/(length+lableAmountMap.size());
    }
    
    //change to probability maxtrices
    for (unsigned long i = 0; i < width; i++)
    {
        mapIter=lableAmountMap.begin();
        for (; mapIter != lableAmountMap.end(); mapIter++)
        {
            std::set<double>::iterator attrIter=attrSets[i].begin();
            for (; attrIter != attrSets[i].end(); attrIter++)
            {
                double &num=conMatrices[i][lableIndexMap[mapIter->first]][conAttrMaps[i][*attrIter]];
                num=(num+1)/(lableAmountMap[mapIter->first]+attrSets[i].size());
            }
        }
    }
}

unsigned long NaiveBayes::classify(double* dataRow,unsigned long width)
{
    unsigned long lable=0;
    double prob=0;
    std::map<unsigned long,double>::iterator iter=lableProbMap.begin();
    for ( ; iter != lableProbMap.end(); iter++)
    {
        double product=iter->second;
        for (unsigned long i = 0; i < width; i++)
        {
            product*=conMatrices[i][lableIndexMap[iter->first]][conAttrMaps[i][*(dataRow+i)]];
        }
        if (product>prob)
        {
            lable=iter->first;
            prob=product;
        }
    }
    return lable;
}
/*
double NaiveBayes::test(double* data, unsigned long width, long* lable, unsigned long length)
{
    unsigned long error=0;
    for (unsigned long i = 0; i < length; i++)
    {
        if (*(lable+i)!=classify(data+i, width))
        {
            error++;
        }
    }
    return 1-(double)error/length;
}*/