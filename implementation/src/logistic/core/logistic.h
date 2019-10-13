#ifndef CORE_LOGISTIC_H
#define CORE_LOGISTIC_H
#include <vector>
#include "common/core/common.h"
#include "common/core/optimizer.h"
namespace patrick
{
    class Logistic : Classifier
    {
    private:
        std::vector<Vector> weights;
    public:
        Logistic(unsigned long k) : weights{k-1}{};
        void train(double* data, unsigned long width, long* lable, unsigned long length);//lable belongs to {0,1,2,...,k-1}
        long classify(double* dataRow,unsigned long width);
    };

    class LogisticDerivative : public FirstOrderDerivative<Vector>
    {
    private:
        std::vector<Vector>& weights;
        unsigned long weightIndex;
    public:
        LogisticDerivative(std::vector<Vector>& weights, unsigned long index) 
            : weights{weights}, weightIndex{index}{};
        Vector operator()(Vector& input);
    };
    
    class LogisticTarget : public TargetFunction<Vector>
    {
    private:
        std::vector<Vector>& weights;
        unsigned long weightIndex;
    public:
        LogisticTarget(std::vector<Vector>& weights, unsigned long index) 
            : TargetFunction{*(new LogisticDerivative{weights, index})}, 
                weights{weights}, weightIndex{index}{};
        ~LogisticTarget();
        double operator()(Vector& input);
    };
    
} // namespace patrick

#endif