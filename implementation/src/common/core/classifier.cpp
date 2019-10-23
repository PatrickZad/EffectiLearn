#include "classifier.h"
#include "./../../exception/exception.h"
using namespace patrick;

double Classifier::test(double* data, unsigned long width, long* lable, unsigned long length)
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
}