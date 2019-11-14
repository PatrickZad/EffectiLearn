#include "./../../src/logistic/core/logistic.h"
#include "common.h"
using namespace patrick;
int main()
{
    DataPtr data=readData(IRIS);
    Logistic logistic{3};
    logistic.train(data.data, data.width, data.lable, data.length);
    logistic.test(data.data, data.width, data.lable, data.length);
    return 0;
}