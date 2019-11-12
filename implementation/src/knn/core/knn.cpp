#include "knn.h"
#include <vector>
#include <map>
using namespace patrick;
void Knn::train(double* data, unsigned long width,unsigned long* lable, unsigned long length)
{
    std::vector<LabledVector> dataVec{};
    for (unsigned long i = 0; i < length; i++)
    {
        LabledVector dataVector{data+i*width, width, *(lable+i)};
        dataVec.push_back(dataVector);
    }
    tree.build(dataVec);
}

unsigned long Knn::classify(double* dataRow,unsigned long width)
{
    Vector data{dataRow,width};
    std::vector<LabledVector> nns=tree.searchNN(data,this->k);
    std::map<unsigned long, unsigned long> countMap;
    for (LabledVector vec : nns)
    {
        if (countMap.count(vec.lable)==0)
        {
            countMap[vec.lable]=1;
        }
        else
        {
            countMap[vec.lable]++;
        }
        
    }
    long lable;
    long count=0;
    std::map<unsigned long, unsigned long>::iterator iter=countMap.begin();
    for (; iter != countMap.end() ; iter++)
    {
        if (iter->second>count)
        {
            lable=iter->first;
            count=iter->second;
        }
    }
    return lable;
}
/*
double Knn::test(double* data, unsigned long width, long* lable, unsigned long length)
{
    unsigned long error=0;
    for (unsigned long i = 0; i < length; i++)
    {
        double* sample=new double[width+1];
        for (unsigned long i = 0; i < width; i++)
        {
            *(sample+i)=*(data+i);
        }
        *(sample+width)=*(lable+i);
        if (*(lable+i)!=classify(sample, width))
        {
            error++;
        }
        delete[] sample;
    }
    return 1-(double)error/length;
}*/