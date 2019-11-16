#include "svm.h"
#include <cmath>
using namespace patrick;
void SVM::train(double* data, unsigned long width, unsigned long* lable, unsigned long length)
{
    //init vectors
    for (unsigned long i = 0; i < length; i++)
    {
        datas.push_back(LabledVector{data+width*i, width, *(lable+i) > 0 ? 1 : -1});
        alphas.push_back(0);
    }
    //smo solve method
    for (unsigned int i = 0; i < maxRepeat; i++)
    {
        //select variables
        unsigned long firstIndex=selectFirstAlpha();
        unsigned long secondIndex=selectSecondAlpha(firstIndex);
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
        //update alphas
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
        //update b
        if (alphas[firstIndex]>0 && alphas[firstIndex]<c)
        {
            b-=bias(firstIndex);
        }else if (alphas[secondIndex]>0 && alphas[secondIndex]<c)
        {
            b-=bias(secondIndex);
        }else
        {
            b=(b-bias(firstIndex)+b-bias(secondIndex))/2;
        }
        //check if ready to stop
        if (earlyStop())
        {
            break;
        }
    }
    
}
unsigned long SVM::classify(double* dataRow,unsigned long width)
{
    Vector data{dataRow, width};
    return originOutput(data)<0 ? 0 : 1 ;
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

unsigned long SVM::selectFirstAlpha()
{
    unsigned long resultIndex=alphas.size();
    double absBias=0;
    unsigned long outIterIndex=alphas.size();
    double absBiasOutIter=0;
    for (unsigned long i = 0; i < alphas.size(); i++)
    {
        double bias=datas[i].lable * originOutput(datas[i])-1;
        double abs=std::abs(bias);
        if (alphas[i]>0 && alphas[i]<c)
        {
            if (abs>minChange && abs>absBias)
            {
                resultIndex=i;
                absBias=abs;
            }
            break;
        }
        if (alphas[i]==0)
        {
            if (bias<(-1*minChange) && abs>absBiasOutIter)
            {
                outIterIndex=i;
                absBiasOutIter=abs;
            }
            break;
        }
        if (bias>minChange && abs>absBiasOutIter)
        {
            outIterIndex=i;
            absBiasOutIter=abs;
        }
    }
    if (resultIndex<alphas.size())
    {
        return resultIndex;
    }else
    if (outIterIndex<alphas.size())
    {
        return outIterIndex;
    }
    return 0;
    
}
unsigned long SVM::selectSecondAlpha(unsigned long firstIndex)
{
    unsigned long resultIndex=alphas.size();
    double absBias=0;
    for (unsigned long i = 0; i < firstIndex; i++)
    {
        double abs=std::abs(bias(firstIndex)-bias(i));
        if (abs>absBias)
        {
            resultIndex=i;
            absBias=abs;
        }
    }
    for (unsigned long i = firstIndex+1; i < alphas.size(); i++)
    {
        double abs=std::abs(bias(firstIndex)-bias(i));
        if (abs>absBias)
        {
            resultIndex=i;
            absBias=abs;
        }
    }
    return resultIndex;
}
bool SVM::earlyStop()
{
    //check KKT
    double sum=0;
    for (unsigned long i = 0; i < alphas.size(); i++)
    {
        sum+=alphas[i]*datas[i].lable;
        if (!checkKKT(i))
        {
            return false;
        }
    }
    if (std::abs(sum)>minChange)
    {
        return false;
    }
    return true;
}
double SVM::bias(unsigned long index)
{
    double result=b-datas[index].lable;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        result+=alphas[i]*datas[i].lable*kernel(datas[i],datas[index]);
    }
    return result;
}
/*
*accuracy check not implemented
*/
bool SVM::checkKKT(unsigned long index)
{
    if (alphas[index]<0 || alphas[index]>c)
    {
        return false;
    }else
    if (alphas[index]==0 && originOutput(datas[index])*datas[index].lable<1)
    {
        return false;
    }else
    if (alphas[index]==c && originOutput(datas[index])*datas[index].lable>1)
    {
        return false;
    }else
    if (originOutput(datas[index])*datas[index].lable!=1)
    {
        return false;
    }
    return true;
}