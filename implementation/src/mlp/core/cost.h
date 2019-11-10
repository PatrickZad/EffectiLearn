#ifndef CORE_COST_H
#define CORE_COST_H
#include "./../../common/core/Vector.h"
#include "./../../common/core/Matrix.h"
#include "mlp.h"
#include <vector>
namespace patrick
{
    class CostFunc
    {
    public:
        virtual double cost(Vector& output)=0;
        virtual Vector derivative(Vector& output)=0;
    };
    class CrossEntropy : public CostFunc
    {
    public:
        double cost(std::vector<LabledVector> datas, std::vector<Vector> outputs);
        Vector derivative(std::vector<LabledVector> datas, std::vector<Vector> outputs);
    };
    /*
    class Regularizer
    {
    public:
        virtual double operator()(Matrix& weights)=0;
    };
    class L2Regularizer : Regularizer
    {
    private:
        double rate;
    public:
        L2Regularizer(double rate) : rate{rate}{};
        double operator()(Matrix& weights);
    };*/
} // namespace patrick

#endif