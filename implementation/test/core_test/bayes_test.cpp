#include "./../../src/bayes/core/bayes.h"
#include "common.h"
int main(){
    DataPtr data=readData(IRIS);
    patrick::NaiveBayes bayes{};
    bayes.train(data.data, data.width, data.lable, data.length);
    bayes.test(data.data, data.width, data.lable, data.length);
    return 0;
}