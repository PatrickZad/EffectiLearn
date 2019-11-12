#include "perceptron.h"
using namespace patrick;

void Perceptron::train(double* dataPtr,unsigned long width, int* lable,unsigned long dataLength){
    double gram[dataLength*(dataLength+1)/2]={0};
    std::vector<patrick::Vector> data;
    for (unsigned long i = 0; i < dataLength; i++)
    {
        Vector dataVector{dataPtr+i*width,width};
        data.push_back(dataVector);
    }
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
    int turns=500;
    unsigned long error=0;
    do
    {
        error=0;
        for (unsigned long i = 0; i < dataLength; i++)
        {
            double result = bias;
            for (long j = 0; j < dataLength; j++)
            {
                result+=a[j]*lable[j]*getGram(gram, dataLength, j, i);
            }
            if (lable[i]*result<=0)
            {
                error++;
                a[i]+=rate;
                bias+=rate*lable[i];
            }
        }
        turns--;
    } while (turns>0 && error>0);
    weight=Vector{width};
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
    return 1-(double)error/length;
}

double Perceptron::getGram(double* gram,unsigned matWidth, unsigned long i, unsigned long j){
    unsigned long row,column;
    if (i>j)
    {
        row=j;
        column=i;
    }else
    {
        row=i;
        column=j;
    }
    unsigned long index=row*matWidth-row*(row-1)/2+column-row;
    return *(gram+index);
}