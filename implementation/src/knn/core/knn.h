#ifndef CORE_KNN_H
#define CORE_KNN_H
#include "./../../common/core/dist_func.h"
#include "./../../common/core/classifier.h"
#include "kdtree.h"
namespace patrick{
    class Knn : public Classifier
    {
    private:
        KDTree tree;
        unsigned long k;
    public:
        Knn(DistanceFunc& distFunc, unsigned long k) : tree{distFunc}, k{k} {};
        void train(double* data, unsigned long width,unsigned long* lable, unsigned long length);
        unsigned long classify(double* dataRow,unsigned long width);
        //double test(double* data, unsigned long width, long* lable, unsigned long length);
    };
    double euclideanDistance();
    double manhattanDistance();
}
#endif