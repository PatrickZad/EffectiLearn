#ifndef CORE_SVM_H
#define CORE_SVM_H
#include "./../../common/core/classifier.h"
#include "./../../common/core/kernel_function.h"
#include "./../../common/core/Vector.h"
#include <vector>
namespace patrick
{     
    class SVM : public Classifier
    {
    private:
        KernelFunction& kernel;
        double c;
        double b;
        std::vector<LabledVector> datas;
        std::vector<double> alphas;
        unsigned int maxRepeat=500;
        double minChange=0.01;
    public:
        SVM(double c, KernelFunction& kernel) : c{c}, kernel{kernel} {};
        void train(double* data, unsigned long width, unsigned long* lable, unsigned long length);
        unsigned long classify(double* dataRow,unsigned long width);
    private:
        double originOutput(Vector& data);
        unsigned long selectFirstAlpha();
        unsigned long selectSecondAlpha(unsigned long firstIndex);
        bool earlyStop();
        double bias(unsigned long index);
        bool checkKKT(unsigned long index);
    };
    
} // namespace patrick

#endif