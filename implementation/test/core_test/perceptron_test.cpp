#include "./../../src/perceptron/core/perceptron.h"
#include "common.h"
#include <string>
int main()
{
    //std::string file="/home/patrick/PatrickWorkspace/LearningAlgorithmsImplementation/implementation/test/dataset/iris_num.data";
    BinaryDataPtr data=readBinaryData(IRIS);
    patrick::Perceptron perceptron{};
    perceptron.train(data.data, data.width, data.lable, data.length);
    perceptron.test(data.data, data.width, data.lable, data.length);
    return 0;
}