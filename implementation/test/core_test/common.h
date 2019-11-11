#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include <vector>
#include <string>
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
    int* lable;
    unsigned long length;
};
DataPtr readData(std::string filepath);
BinaryDataPtr readBinaryData(std::string filepath);
std::vector<std::string> split(std::string& str, char c);
double str2float(std::string& str);
unsigned long lableStr2Int(std::string& str);
#endif