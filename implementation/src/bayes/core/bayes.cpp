#include "bayes.h"
#include "common/core/common.h"
using namespace patrick;

void NaiveBayes::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    for (unsigned long i = 0; i < length; i++)
    {
        Vector sample{data+i,width};
        for (unsigned long j = 0; i < width; j++)
        {
            
            
        }
        
    }
    
}