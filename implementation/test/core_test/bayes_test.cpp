#include "./../../src/bayes/core/bayes.h"
#include "common.h"
int main(){
    DataPtr data=readData("./dataset/iris_num.data");
    patrick::NaiveBayes bayes{};
    bayes.train(data.data, data.width, data.lable, data.length);
    return 0;
}