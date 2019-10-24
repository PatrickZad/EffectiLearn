#ifndef CORE_SVM_H
#define CORE_SVM_H
#include "./../../common/core/classifier.h"
#include "./../../common/core/kernel_function.h"
#include "./../../common/core/Vector.h"
#include <vector>
namespace patrick
{
    class SVM : Classifier
    {
    private:
        KernelFunction& kernel;
        double c;
        double b;
        std::vector<LabledVector> datas;
        std::vector<double> alphas;
    public:
        SVM(double c, KernelFunction& kernel) : c{c}, kernel{kernel} {};
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        long classify(double* dataRow,unsigned long width);
    };
    
} // namespace patrick

#endif