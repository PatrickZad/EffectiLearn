#ifndef CORE_CLASSIFIER_H
#define CORE_CLASSIFIER_H
#include "Vector.h"
namespace patrick
{
    class Classifier
    {
    public:
        virtual void train(double* data, unsigned long width,unsigned long* lable, unsigned long length)=0;
        virtual unsigned long classify(double* dataRow,unsigned long width)=0;
        double test(double* data, unsigned long width, unsigned long* lable, unsigned long length);
    };
    
} // namespace patrick

#endif