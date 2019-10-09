#include "bayes.h"
#include "common/core/common.h"
#include <set>
using namespace patrick;

void NaiveBayes::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    //build lable map
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
            lableIndexMap[*(lable+i)]=1;
        }
        else
        {
            lableIndexMap[*(lable+i)]++;
        }
    }
    //build attrribute sets
    std::vector<std::set<double>> attrSets{width};
    for (unsigned long i = 0; i < length; i++)
    {
        for (unsigned long j = 0; j < width; j++)
        {
            attrSets[j].insert((data+i)[j]);
        }
    }
    //build attribute map
    for (unsigned long i = 0; i < width; i++)
    {
        std::set<double>::iterator iter;
        unsigned long index=0;
        for (iter = attrSets[i].begin(); iter != attrSets[i].end; iter++)
        {
            conAttrMaps[i][*iter]=index;
            index++;
        }
           
    }
    //initialize matrices
    for (unsigned long i = 0; i < width; i++)
    {
        std::vector<std::vector<unsigned long>> conMatrix{lableIndexMap.size()};
        for (unsigned long j = 0; j < lableIndexMap.size(); j++)
        {
            conMatrix[j]=std::vector<unsigned long> {attrSets[i].size(),0};
        }
        conMatrices.push_back(conMatrix);
    }
    //counting amount
    for (unsigned long i = 0; i < length; i++)
    {
        Vector sample{data+i,width};
        for (unsigned long j = 0; j < width; j++)
        {
            unsigned long valueIndex=conAttrMaps[j][sample[j]];
            conMatrices[j][*(lable+i)][valueIndex]++;
        }
    }
    
}