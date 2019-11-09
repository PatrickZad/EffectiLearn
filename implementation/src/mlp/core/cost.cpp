#include "cost.h"
#include <cmath>
using namespace patrick;
double CrossEntropy::cost(std::vector<LabledVector> datas, std::vector<Vector> outputs)
{
    double result=0;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        result-=std::log(outputs[i][datas[i].lable]);
    }
    return result;
}

Vector CrossEntropy::derivative(std::vector<LabledVector> datas, std::vector<Vector> outputs)
{
    Vector result{outputs[0].size()};
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        result[datas[i].lable]-=1/outputs[i][datas[i].lable];
    }
    return result;
}