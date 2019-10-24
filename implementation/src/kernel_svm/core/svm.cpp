#include "svm.h"
using namespace patrick;
void SVM::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    //init vectors
    for (unsigned long i = 0; i < length; i++)
    {
        datas.push_back(LabledVector{data+width*i, width, *(lable+i)});
        alphas.push_back(0);
    }
    
}
long SVM::classify(double* dataRow,unsigned long width)
{
    Vector data{dataRow, width};
    double result=b;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        result+=alphas[i]*datas[i].lable*kernel(data, datas[i]);
    }
    return result<0 ? -1 : 1 ;
}