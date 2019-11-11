#include "perceptron.h"
using namespace patrick;
Perceptron::Perceptron(double* dataArray,unsigned long width, int* lable, unsigned long length)
: dataWidth{width},dataLength{length},weight{width},lable{length},bias{0}
{
    for (long i = 0; i < length; i++)
    {
        Vector dataVector{dataArray+i*width,width};
        data.push_back(dataVector);
    }
}

void Perceptron::train(double rate){
    double gram[dataLength*(dataLength+1)/2]={0};
    unsigned long turn;
    for (unsigned long i = 0; i < dataLength; i++)
    {
        for (unsigned long j = i; j < dataLength; j++)
        {
            unsigned long index=i*dataLength-i*(i-1)/2+j-i;
            gram[index]=data[i]*data[j];
        }
    }
    
    double a[dataLength]={0};
    int turns=200;
    long error=0;
    do
    {
        error=0;
        for (long i = 0; i < dataLength; i++)
        {
            double result = bias;
            for (long j = 0; j < dataLength; j++)
            {
                result+=a[j]*lable[j]*getGram(gram,j,i);
            }
            if (lable[i]*result<=0)
            {
                error++;
                a[i]+=rate;
                bias+=rate*lable[i];
            }
        }
        
    } while (turns>0 || error>0);
    for (long i = 0; i < dataLength; i++)
    {
        weight+=data[i]*a[i]*lable[i];
    }
}

int Perceptron::classify(double* dataRow, unsigned long width){
    Vector data{dataRow,width};
    double result=weight*data+bias;
    return result>0 ? 1 : -1 ;
}

double Perceptron::test(double* data, unsigned long width, int* lable, unsigned long length){
    long error=0;
    for (long i = 0; i < length; i++)
    {
        if (classify(data+i*width,width)!=*(lable+i))
        {
            error++;
        }
    }
    return (double)error/length;
}

double Perceptron::getGram(double* gram, unsigned long i, unsigned long j){
    long row,column;
    if (i>j)
    {
        row=j;
        column=i;
    }else
    {
        row=i;
        column=j;
    }
    return *(gram+row*(2*dataLength-row+1)/2+j);
}