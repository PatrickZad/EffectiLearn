#ifndef CORE_ADABOOST_H
#define CORE_ADABOOST_H
#include "./../../common/core/classifier.h"
#include <vector>
namespace patrick
{
    class AdaBoost : Classifier
    {
    private:
        std::vector<double> weights;
        std::vector<Classifier> classifiers;
    public:
        AdaBoost(std::vector<Classifier>& classifiers) : classifiers{classifiers} {};
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        long classify(double* dataRow,unsigned long width);
    };
    
} // namespace patrick


#endif