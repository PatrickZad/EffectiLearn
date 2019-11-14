#ifndef CORE_DECISION_TREE_H
#define CORE_DECISION_TREE_H
#include <set>
#include <map>
#include <vector>
#include "./../../common/core/classifier.h"
#include "attr_select.h" 
namespace patrick
{
    class DtNode
    {
    public:
        Attr branchAttr;
        //key specifies which subNode to branch
        //and for continuos attribute, 1 means larger, -1 means smaller
        std::map<double,DtNode*> subNodes; 
        unsigned long lable;
    };
    

    class DecisionTree : public Classifier
    {
    private:
        DtNode* root;
        AttrSelecter& selecter;
    public:
        DecisionTree(AttrSelecter& selecter):root{nullptr}, selecter{selecter}{};
        ~DecisionTree();
        DecisionTree(const DecisionTree& tree);
        DecisionTree(DecisionTree&& tree);

        DecisionTree& operator=(const DecisionTree& tree);
        DecisionTree& operator=(DecisionTree&& tree);

        void train(double* data, unsigned long width, unsigned long* lable, unsigned long length);
        void train(double* data, unsigned long width, unsigned long* lable, unsigned long length,std::vector<unsigned long> discretAttrs);
        unsigned long classify(double* dataRow,unsigned long width);
    private:
        void buildTree(DtNode* root, std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
        void releaseTree(DtNode* root);
        void copyTree(DtNode* destRoot, DtNode* srcRoot);
    };
    
} // namespace patrick

#endif