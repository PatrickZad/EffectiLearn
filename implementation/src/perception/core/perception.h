#ifndef CORE_PERCEPTION_H
#define CORE_PERCEPTION_H
#include "common/core/common.h"
#include <vector>

namespace patrick{
    class Perception
    {
    private:
        long dataWidth;
        long dataLength;
        patrick::Vector weight;
        double bias;
        std::vector<patrick::Vector> data;
        patrick::Vector lable;

    public:
        Perception(double* data, long width, int* lable, long length); 
        void train(double rate=0.1);//nonnumeric lables should be transfered to int value
        int classify(double* dataRow,long width);//return index of type in typeColumn
    private:
        double getGram(double* gram,long i, long j);
    };

    class DescriminationFunc
    {
    public:

        DescriminationFunc();
        ~DescriminationFunc();
    };
    
}



#endif