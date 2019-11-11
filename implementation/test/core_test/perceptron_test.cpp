#include "./../../src/perceptron/core/perceptron.h"
#include "common.h"
#include <string>
int main()
{
    std::string file="/home/patrick/PatrickWorkspace/LearningAlgorithmsImplementation/implementation/test/dataset/iris_num.data";
    BinaryDataPtr data=readBinaryData(file);
    patrick::Perceptron perceptron{data.data, data.width, data.lable, data.length};
    perceptron.train();
    return 0;
}