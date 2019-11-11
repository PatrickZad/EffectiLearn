#ifndef CORE_BAYES_H
#define CORE_BAYES_H
#include <map>
#include <vector>
#include "./../../common/core/classifier.h"
namespace patrick{
    class NaiveBayes:Classifier
    {
    private:
        std::vector<std::vector<std::vector<double>>> conMatrices;//elements are pointers of matrix counting samples by lables-attributs
        std::vector<std::map<double,unsigned long>> conAttrMaps;//attr_value-maxtrix_index sets
        std::map<unsigned long, unsigned long> lableIndexMap;//lable-maxtrix_index sets
        std::map<unsigned long,double> lableProbMap;
    public:
        void train(double* data, unsigned long width,unsigned long* lable, unsigned long length);
        unsigned long classify(double* dataRow,unsigned long width);
        //double test(double* data, unsigned long width, long* lable, unsigned long length);
    };
}
#endif