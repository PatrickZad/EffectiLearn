//
// Created by Administrator on 11/16/2019.
//
#include "common.h"
#include "./../../src/kernel_svm/core/svm.h"
#include "./../../src/common/core/kernel_function.h"
int main()
{
    BinaryDataPtr data=readBinaryData(IRIS_WIN );
    patrick::GaussianKernel kernel;
    patrick::SVM svm{1, kernel};
    svm.train(data.data, data.width, data.lable, data.length);
    svm.test(data.data, data.width, data.lable, data.length);
    return 0;
}
