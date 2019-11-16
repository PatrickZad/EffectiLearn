#ifndef CORE_LOGISTIC_H
#define CORE_LOGISTIC_H
#include <vector>
#include <map>
#include "./../../common/core/classifier.h"
#include "./../../common/core/optimizer.h"
#include "./../../common/core/Vector.h"
#include "./../../common/core/Matrix.h"
namespace patrick
{
    class Logistic : public Classifier
    {
    private:
        Matrix weights;
        unsigned long k;
    public:
        void train(double* data, unsigned long width, unsigned long* lable, unsigned long length);//lable belongs to {0,1,2,...,k-1}
        unsigned long classify(double* dataRow,unsigned long width);
    };

    class LogisticDerivative : public FirstOrderDerivative<Matrix>
    {
    private:
        std::map<unsigned long, std::vector<Vector>> lableDataMap;
    public:
        LogisticDerivative(std::map<unsigned long, std::vector<Vector>>& lableDataMap)
                : lableDataMap{lableDataMap} {};
        Matrix operator()(Matrix& weights);
    };
    
    class LogisticTarget : public TargetFunction<Matrix>
    {
    private:
        std::map<unsigned long, std::vector<Vector>> lableDataMap;
    public:
        LogisticTarget(std::map<unsigned long, std::vector<Vector>>& lableDataMap) 
            : TargetFunction{*(new LogisticDerivative{lableDataMap})}, lableDataMap{lableDataMap} {};
        ~LogisticTarget();
        double operator()(Matrix& weights);
    };
    
} // namespace patrick

#endif