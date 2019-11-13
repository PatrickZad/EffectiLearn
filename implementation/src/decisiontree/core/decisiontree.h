#ifndef CORE_DECISION_TREE_H
#define CORE_DECISION_TREE_H
#include <set>
#include <map>
#include <vector>
#include "./../../common/core/classifier.h"
#include "attr_select.h" 
namespace patrick
{
    class Attr
    {
    public:
        unsigned long index;
        bool isContinuos=true;
        //for discrete attribute, contains all possible values; 
        //for continuos attribute, contains all values exit in tarin set
        //and after AttributeSelct, contarins only the value used to branch
        std::set<double> branchValues;
    };
    
    class DtNode
    {
    public:
        Attr branchAttr;
        std::map<double,DtNode*> subNodes; 
        long lable;
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