#ifndef CORE_PERCEPTRON_H
#define CORE_PERCEPTRON_H
#include "./../../common/core/Vector.h"
#include <vector>

namespace patrick{
    class Perceptron
    {
    private:
        unsigned long dataWidth;
        patrick::Vector weight;
        double bias;
        double rate=0.1;
    public:
        void train(double* data,unsigned long width, int* lable,unsigned long length);//nonnumeric lables should be transfered to int value
        int classify(double* dataRow,unsigned long width);//return index of type in typeColumn
        double test(double* data,unsigned long width, int* lable, unsigned long length);
    private:
        double getGram(double* gram, unsigned matWidth, unsigned long i, unsigned long j);
    };

    class DescriminationFunc
    {
    public:

        DescriminationFunc();
        ~DescriminationFunc();
    };
    
}



#endif