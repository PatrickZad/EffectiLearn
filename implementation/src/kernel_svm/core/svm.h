#ifndef CORE_SVM_H
#define CORE_SVM_H
#include "./../../common/core/classifier.h"
namespace patrick
{
    class SVM : Classifier
    {
    private:
        /* data */
    public:
        SVM(/* args */);
        ~SVM();
    };
    
    SVM::SVM(/* args */)
    {
    }
    
    SVM::~SVM()
    {
    }
    
} // namespace patrick

#endif