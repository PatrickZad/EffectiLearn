#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include <vector>
#include <string>
const std::string IRIS="/home/patrick/PatrickWorkspace/LearningAlgorithmsImplementation/implementation/test/dataset/iris_num.data";
const  std::string IRIS_WIN="F:\\LearningAlgorithmsImplementation\\implementation\\test\\dataset\\iris_num.data";
struct DataPtr
{
    double* data;
    unsigned long width;
    unsigned long* lable;
    unsigned long length;
};
struct BinaryDataPtr
{
    double* data;
    unsigned long width;
    unsigned long* lable;
    unsigned long length;
};
DataPtr readData(std::string filepath);
BinaryDataPtr readBinaryData(std::string filepath);
std::vector<std::string> split(std::string& str, char c);
double str2float(std::string& str);
unsigned long lableStr2Int(std::string& str);
#endif