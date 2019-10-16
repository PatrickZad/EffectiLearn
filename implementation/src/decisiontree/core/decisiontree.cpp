#include "decisiontree.h"
#include "common/core/Vector.h"
using namespace patrick;
DecisionTree::~DecisionTree(){
    releaseTree(root);
}

DecisionTree::DecisionTree(const DecisionTree& tree)
{
    root=new DtNode{};
    copyTree(root, tree.root);
}

DecisionTree::DecisionTree(DecisionTree&& tree)
{
    root=tree.root;
    tree.root=nullptr;
}

DecisionTree& DecisionTree::operator=(const DecisionTree& tree)
{
    releaseTree(root);
    root=new DtNode{};
    copyTree(root, tree.root);
}

DecisionTree& DecisionTree::operator=(DecisionTree&& tree)
{
    releaseTree(root);
    root=tree.root;
    tree.root=nullptr;
}

void DecisionTree::train(double* data, unsigned long width, long* lable, unsigned long length)
{
    train(data,width,lable,length,std::vector<unsigned long>{});
}

void DecisionTree::train(double* data, unsigned long width, long* lable, unsigned long length,std::vector<unsigned long> discretIndex)
{
    std::vector<Attr> attrs{width};
    //set Attr isContinuos member
    for (unsigned long index : discretIndex)
    {
        attrs[index].isContinuos=false;
    }
    //set Attr index
    for (unsigned long i=0; i<width; i++)
    {
        attrs[i].index=i;
    }

    std::vector<LabledVector> datas{};
    //build datas and discrete attribute value set
    for (unsigned long i = 0; i < length; i++)
    {
        LabledVector dataVec{data+i*width, width, *(lable+i)};
        datas.push_back(dataVec);
        for (unsigned long j = 0; j < width; i++)
        {
            attrs[j].branchValues.insert(dataVec[j]);
        }
    }
    root = new DtNode{};
    buildTree(root, datas, attrs);
}

long DecisionTree::classify(double* dataRow,unsigned long width)
{
    DtNode* node=root;
    while (node->subNodes.size()!=0)
    {
        if (node->branchAttr.isContinuos)
        {
            if(*(dataRow+node->branchAttr.index)
                >*(node->branchAttr.branchValues.begin))
            {
                node=node->subNodes[1];
            }else
            {
                node=node->subNodes[0];
            }
        }else
        {
            node=node->subNodes[*(dataRow+node->branchAttr.index)];
        }        
    }
    return node->lable;
}

void DecisionTree::buildTree(DtNode* root, std::vector<LabledVector>& datas, std::vector<Attr>& attrs)
{
    //return when only one kind of lable
    long dataLable=datas[0].lable;
    std::vector<LabledVector>::iterator iter=(datas.begin()++);
    bool oneLable=true;
    for(;iter!=datas.end();iter++)
    {
        if (iter->lable!=dataLable)
        {
            oneLable=false;
            break;
        }
    }   
    if (oneLable)
    {
        root->lable=dataLable;
        return;
    }
    //return when no attr left or data values are equal on given attrs
    bool noBranch=true;
    if (attrs.size()!=0)
    {
        std::map<unsigned long, double> attrindexValueMap;
        iter=datas.begin();
        for (Attr a : attrs)
        {
            attrindexValueMap[a.index]=(*iter)[a.index];
        }
        for (iter++;iter!=datas.end(); iter++)
        {
            for (Attr a : attrs)
            {
                if(attrindexValueMap[a.index]!=(*iter)[a.index])
                {
                    noBranch=false;
                    break;
                }
            }
            if (!noBranch)
            {
                break;
            }
        }
    }
    if (noBranch)
    {
        std::map<long, unsigned long> lableAmountMap;
        iter=datas.begin();
        for (;iter!=datas.end(); iter++)
        {
            if (lableAmountMap.count(iter->lable)==0)
            {
                lableAmountMap[iter->lable]=1;
            }else
            {
                lableAmountMap[iter->lable]+=1;
            }
        }
        std::map<long, unsigned long>::iterator mapIter=lableAmountMap.begin();
        unsigned long maxAmount=mapIter->second;
        dataLable=mapIter->first;
        for(;mapIter!=lableAmountMap.end();mapIter++)
        {
            if (mapIter->second>maxAmount)
            {
                maxAmount=mapIter->second;
                dataLable=mapIter->first;
            }   
        }
        root->lable=dataLable;
        return;
    }
    //branch
    Attr branchAttr=selecter(datas,attrs);
    root->branchAttr=branchAttr;
    std::vector<Attr> newAttrs;
    for(Attr attr : attrs)
    {
        if (attr.index!=branchAttr.index)
        {
            newAttrs.push_back(attr);
        }
    }
    iter=datas.begin();
    if (branchAttr.isContinuos)
    {
        std::vector<LabledVector> smallerDatas;
        std::vector<LabledVector> largerDatas;
        for (; iter!=datas.end(); iter++)
        {
            if ((*iter)[branchAttr.index]>*(branchAttr.branchValues.begin()))
            {
                largerDatas.push_back(*iter);
            }else
            {
                smallerDatas.push_back(*iter);
            }
        }
        root->subNodes[0]=new DtNode{};
        root->subNodes[1]=new DtNode{};
        buildTree(root->subNodes[0], smallerDatas, newAttrs);
        buildTree(root->subNodes[1], largerDatas, newAttrs);
    }else
    {
        std::map<double, std::vector<LabledVector>> attrvalueDatas;
        //build attrvalueDatas map
        for (; iter != datas.end(); iter++)
        {
            if (attrvalueDatas.count((*iter)[branchAttr.index])==0)
            {
                attrvalueDatas[(*iter)[branchAttr.index]]=std::vector<LabledVector>{};
            }
            attrvalueDatas[(*iter)[branchAttr.index]].push_back(*iter);
        }//end of build
        std::set<double>::iterator setIter=branchAttr.branchValues.begin();
        //build branches
        for(; setIter!=branchAttr.branchValues.end() ; setIter++)
        {
            root->subNodes[*setIter]=new DtNode{};
            buildTree(root->subNodes[*setIter], attrvalueDatas[*setIter], newAttrs);
        }
    }
    
}
void DecisionTree::releaseTree(DtNode* root)
{}
void DecisionTree::copyTree(DtNode* destRoot, DtNode* srcRoot)
{}