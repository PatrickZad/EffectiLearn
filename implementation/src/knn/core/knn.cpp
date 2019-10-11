#include "knn.h"
#include <vector>
#include <map>
using namespace patrick;
 Knn::Knn(DistanceFunc& distFunc, unsigned long k):k{k}
{
    tree.setDistFunc(distFunc);
}

void Knn::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    std::vector<Vector> dataVec{};
    for (unsigned long i = 0; i < length; i++)
    {
        Vector dataVector{data+i*width,width};
        double lableD=*(lable+i);
        dataVec.push_back(dataVector.concat(Vector{&lableD,1}));
    }
    tree.build(dataVec);
}

long Knn::classify(double* dataRow,unsigned long width)
{
    Vector data{dataRow,width};
    std::vector<Vector> nns=tree.searchNN(data,this->k);
    std::map<long, unsigned long> countMap;
    for (Vector vec : nns)
    {
        long lable=vec[vec.size()-1];
        if (countMap.count(lable)==0)
        {
            countMap[lable]=1;
        }
        else
        {
            countMap[lable]++;
        }
        
    }
    long lable;
    long count=0;
    std::map<long, unsigned long>::iterator iter=countMap.begin();
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