#ifndef CORE_LOGISTIC_H
#define CORE_LOGISTIC_H
#include <vector>
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
        Logistic(unsigned long k) : k{k}{};
        void train(double* data, unsigned long width, unsigned long* lable, unsigned long length);//lable belongs to {0,1,2,...,k-1}
        unsigned long classify(double* dataRow,unsigned long width);
    };

    class LogisticDerivative : public FirstOrderDerivative<Matrix>
    {
    private:
        std::vector<Matrix>& bMatrices;
        std::vector<Vector>& datas;
        std::vector<unsigned long>& lables;
    public:
        LogisticDerivative(std::vector<Matrix>& bMatrices, std::vector<Vector>& datas, 
            std::vector<unsigned long>& lables) 
                : bMatrices{bMatrices}, datas{datas}, lables{lables}{};
        Matrix operator()(Matrix& weights);
    };
    
    class LogisticTarget : public TargetFunction<Matrix>
    {
    private:
        std::vector<Vector> datas;
        std::vector<unsigned long> lables;
    public:
        LogisticTarget(std::vector<Matrix>& bMatrices, std::vector<Vector>& datas, 
            std::vector<unsigned long>& lables) 
            : TargetFunction{*(new LogisticDerivative{bMatrices, datas, lables})}, 
                datas{datas}, lables{lables}{};
        ~LogisticTarget();
        double operator()(Matrix& weights);
    };
    
} // namespace patrick

#endif