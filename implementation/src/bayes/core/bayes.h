#ifndef CORE_BAYES_H
#define CORE_BAYES_H
#include <map>
#include <vector>
namespace patrick{
    class NaiveBayes
    {
    private:
        std::vector<std::vector<std::vector<unsigned long>>> conMatrices;//elements are pointers of matrix counting samples by lables-attributs
        std::vector<std::map<double,unsigned long>> conAttrMaps;//attr_value-maxtrix_index sets
        std::map<long, unsigned long> lableIndexMap;//lable-maxtrix_index sets
        std::map<long,unsigned long> lableAmountMap;
    public:
        NaiveBayes();
        void train(double* data, unsigned long width, long* lable, unsigned long length);
        long classify(double* dataRow,unsigned long width);
        double test(double* data, unsigned long width, long* lable, unsigned long length);
    };
}
#endif