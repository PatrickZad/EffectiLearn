#ifndef CORE_COMMON_H
#define CORE_COMMON_H
#include "Vector.h"
namespace patrick
{
    class DistanceFunc
    {
    public:
        virtual double operator()(Vector& vec0, Vector& vec1)=0;
    };

    class Classifier
    {
    public:
        virtual void train(double* data, unsigned long width, long* lable, unsigned long length)=0;
        virtual long classify(double* dataRow,unsigned long width)=0;
        double test(double* data, unsigned long width, long* lable, unsigned long length);
    };
    
} // namespace patrick

#endif