#include "common.h"
#include "./../../src/knn/core/knn.h"
#include "./../../src/common/core/dist_func.h"
int main()
{
    DataPtr data=readData(IROS_WIN);
    patrick::EuclideanDist distFunc;
    patrick::Knn knn{distFunc, 8};
    knn.train(data.data, data.width, data.lable, data.length);
    knn.test(data.data, data.width, data.lable, data.length);
    return 0;
}