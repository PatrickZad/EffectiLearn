#ifndef CORE_BAYES_H
#define CORE_BAYES_H
#include <map>
#include <vector>
namespace patrick{
    class NaiveBayes
    {
    private:
        std::vector<std::vector<std::vector<unsigned long>>> conMatrix;//elements are pointers of matrix counting samples by lables-attributs
        std::vector<std::map<double,unsigned long>> conAttrMap;//attr_value-maxtrix_index sets
        std::map<long, unsigned long> lableMap;//lable-maxtrix_index sets
    
    public:
        NaiveBayes();
        void train(double* data, long width, int* lable, long length);
        long classify(double* dataRow,long width);
        double test(double* data, long width, int* lable, long length);
    };
}
#endif