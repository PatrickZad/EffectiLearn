#ifndef CORE_PERCEPTRON_H
#define CORE_PERCEPTRON_H
#include "./../../common/core/Vector.h"
#include <vector>

namespace patrick{
    class Perceptron
    {
    private:
        unsigned long dataWidth;
        unsigned long dataLength;
        patrick::Vector weight;
        double bias;
        std::vector<patrick::Vector> data;
        patrick::Vector lable;
        double rate;

    public:
        Perceptron(double* data,unsigned long width, int* lable,unsigned long length); 
        void train(double rate=0.1);//nonnumeric lables should be transfered to int value
        int classify(double* dataRow,unsigned long width);//return index of type in typeColumn
        double test(double* data,unsigned long width, int* lable, unsigned long length);
    private:
        double getGram(double* gram,unsigned long i, unsigned long j);
    };

    class DescriminationFunc
    {
    public:

        DescriminationFunc();
        ~DescriminationFunc();
    };
    
}



#endif