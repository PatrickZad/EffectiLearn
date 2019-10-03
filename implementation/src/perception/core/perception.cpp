#include "perception.h"
using namespace patrick;
Perception::Perception(double* data, long width, int* lable, long length)
: weight{width},lable{length},bias{0}
{

}
void Perception::train(double rate){
    //TODO improvment matrix calculation and storage
    double gram[dataLength][dataLength];
    for (long i = 0; i < dataLength; i++)
    {
        for (long j = 0; j < dataLength; j++)
        {
            gram[i][j]=data[i]*data[j];
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
                result+=a[j]*lable[j]*(data[j]*data[i]);
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

int Perception::classify(double* dataRow,long width){
    Vector data{dataRow,width};
    double result=weight*data+bias;
    return result>0 ? 1 : -1 ;
}