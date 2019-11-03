#include "svm.h"
#include <cmath>
using namespace patrick;
void SVM::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    //init vectors
    for (unsigned long i = 0; i < length; i++)
    {
        datas.push_back(LabledVector{data+width*i, width, *(lable+i)});
        alphas.push_back(0);
    }
    //smo solve method
    for (unsigned int i = 0; i < maxRepeat; i++)
    {
        //select variables
        unsigned long firstIndex=selectFirstAlpha();
        unsigned long secondIndex=selectSecondAlpha();
        //calculate new values
        double left,right;
        if (datas[firstIndex].lable==datas[secondIndex].lable)
        {
            left=std::max(0.0, alphas[firstIndex]+alphas[secondIndex]-c);
            right=std::min(c, alphas[firstIndex]+alphas[secondIndex]);
        }else
        {
            left=std::max(0.0, alphas[secondIndex]-alphas[firstIndex]);
            right=std::min(c,c+alphas[secondIndex]-alphas[firstIndex]);
        }
        double eta=kernel(datas[firstIndex],datas[firstIndex])+kernel(datas[secondIndex],
            datas[secondIndex])-2*kernel(datas[firstIndex], datas[secondIndex]);
        double newUncutSecond=alphas[secondIndex]+datas[secondIndex].lable
            *(bias(firstIndex)-bias(secondIndex))/eta;
        //update varibles
        double secondOld=alphas[secondIndex];
        if (newUncutSecond>right)
        {
            alphas[secondIndex]=right;
        }else if (newUncutSecond<left)
        {
            alphas[secondIndex]=left;
        }else
        {
            alphas[secondIndex]=newUncutSecond;
        }
        alphas[firstIndex]=alphas[firstIndex]+datas[firstIndex].lable * datas[secondIndex].lable
            *(secondOld-alphas[secondIndex]);
        //check if ready to stop
        if (earlyStop())
        {
            break;
        }
    }
    
}
long SVM::classify(double* dataRow,unsigned long width)
{
    Vector data{dataRow, width};
    return originOutput(data)<0 ? -1 : 1 ;
}

double SVM::originOutput(Vector& data)
{
    double result=b;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        result+=alphas[i]*datas[i].lable*kernel(data, datas[i]);
    }
    return result;
}
