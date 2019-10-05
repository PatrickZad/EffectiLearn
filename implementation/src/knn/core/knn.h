#ifndef CORE_KNN_H
#define CORE_KNN_H
#include "common/core/common.h"
namespace patrick{
    class Knn
    {
    private:
        /* data */
    public:
        Knn(/* args */);
        ~Knn();
    };
    double euclideanDistance();
    double manhattanDistance();
}
#endif