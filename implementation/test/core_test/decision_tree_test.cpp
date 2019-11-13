#include "./../../src/decisiontree/core/decisiontree.h"
#include "./../../src/decisiontree/core/attr_select.h"
#include "common.h"
int main()
{
    using namespace patrick;
    DataPtr data=readData(IRIS);
    GainRatio attrselect;
    DecisionTree dtree{attrselect};
    dtree.train(data.data, data.width, data.lable, data.length);
    dtree.test(data.data, data.width, data.lable, data.length);
    return 0;
}