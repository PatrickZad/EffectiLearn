#ifndef CORE_KNN_H
#define CORE_KNN_H
#include "common/core/common.h"
#include "kdtree.h"
namespace patrick{
    class Knn
    {
    private:
        KDTree tree;
        unsigned long k;
    public:
        Knn(DistanceFunc distFunc, unsigned long k);
        
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        long classify(double* dataRow,unsigned long width);
        double test(double* data, unsigned long width, long* lable, unsigned long length);
    };
    double euclideanDistance();
    double manhattanDistance();
}
#endif