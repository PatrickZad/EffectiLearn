#include "attr_select.h"
#include <set>
#include <cmath>
#include <map>
#include <vector>
using namespace patrick;
Attr InformationGain::operator()(std::vector<LabledVector> &datas, std::vector<Attr> &attrs)
{
    //common constant will not be calculated
    Attr result;
    double gain=-1;
    std::set<double> attrBranchValues;
    for (Attr& attr : attrs)
    {
        if (attr.isContinuos)
        {
            std::set<double> valueset;
            for (unsigned long i = 0; i < datas.size(); ++i)
            {
                valueset.insert(datas[i][attr.index]);
            }
            std::vector<double> branchValues;//binary branch values
            std::set<double>::iterator iter=valueset.begin();
            double prevar=*iter;
            double nextvar;
            for (++iter;iter!=valueset.end(); iter++)
            {
                //build branchValues
                nextvar=*iter;
                branchValues.push_back((prevar+nextvar)/2);
                prevar=nextvar;
            }
            std::map<double, std::vector<LabledVector>> valueDataMap;
            double gainAttr=-1;
            double bestBranchValue;
            //select best branch value
            for (std::vector<double>::iterator i = branchValues.begin(); i != branchValues.end(); i++)
            {
                std::vector<LabledVector> smaller;
                std::vector<LabledVector> larger;
                for (std::vector<LabledVector>::iterator j = datas.begin(); j !=datas.end() ; j++)
                {
                    if ((*j)[attr.index]<*i)
                    {
                        smaller.push_back(*j);
                    }else
                    {
                        larger.push_back(*j);
                    }
                }
                double gainBranch=smaller.size()*informationEntropy(smaller)+larger.size()*informationEntropy(larger);
                if (gainBranch<gainAttr || gainAttr<0)
                {
                    gainAttr=gainBranch;
                    bestBranchValue=*i;
                }
            }
            if (gainAttr<gain || gain<0)
            {
                gain=gainAttr;
                attrBranchValues.clear();
                attrBranchValues.insert(bestBranchValue);
                result=attr;
            }
        }else
        {
            std::set<double> branchValues;
            std::map<double, std::vector<LabledVector>> valueDataMap;
            for (unsigned long i = 0; i < datas.size(); ++i)
            {
                branchValues.insert(datas[i][attr.index]);
                valueDataMap[datas[i][attr.index]].push_back(datas[i]);
            }
            double gainAttr=0;
            for (std::map<double, std::vector<LabledVector>>::iterator iter = valueDataMap.begin(); iter!=valueDataMap.end(); iter++)
            {
                gainAttr+=iter->second.size()*informationEntropy(iter->second);
            }
            if (gainAttr<gain || gain<0)
            {
                gain=gainAttr;
                attrBranchValues=branchValues;
                result=attr;
            }
        }
    }
    result.branchValues=attrBranchValues;
    return result;
}

Attr GainRatio::operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs)
{
    Attr result;
    double gain=0;
    std::set<double> attrBranchValues;
    double dataEnt=informationEntropy(datas);
    for (Attr& attr : attrs)
    {
        double intrinsic=intrinsicValue(datas, attr);
        if (attr.isContinuos)
        {
            std::set<double> valueset;
            for (unsigned long i = 0; i < datas.size(); ++i)
            {
                valueset.insert(datas[i][attr.index]);
            }
            std::vector<double> branchValues;//binary branch values
            std::set<double>::iterator iter=valueset.begin();
            double prevar=*iter;
            double nextvar;
            for (++iter;iter!=valueset.end(); iter++)
            {
                //build branchValues
                nextvar=*iter;
                branchValues.push_back((prevar+nextvar)/2);
                prevar=nextvar;
            }
            std::map<double, std::vector<LabledVector>> valueDataMap;
            double gainAttr=0;
            double bestBranchValue;
            //select best branch value
            for (std::vector<double>::iterator i = branchValues.begin(); i != branchValues.end(); i++)
            {
                std::vector<LabledVector> smaller;
                std::vector<LabledVector> larger;
                for (std::vector<LabledVector>::iterator j = datas.begin(); j !=datas.end() ; j++)
                {
                    if ((*j)[attr.index]<*i)
                    {
                        smaller.push_back(*j);
                    }else
                    {
                        larger.push_back(*j);
                    }
                }
                double gainBranch=(dataEnt-(smaller.size()*informationEntropy(smaller)+larger.size()*informationEntropy(larger))/datas.size())/intrinsic;
                if (gainBranch>gainAttr)
                {
                    gainAttr=gainBranch;
                    bestBranchValue=*i;
                }
            }
            if (gainAttr>gain)
            {
                gain=gainAttr;
                attrBranchValues.clear();
                attrBranchValues.insert(bestBranchValue);
                result=attr;
            }
        }else
        {
            std::set<double> branchValues;
            std::map<double, std::vector<LabledVector>> valueDataMap;
            for (unsigned long i = 0; i < datas.size(); ++i)
            {
                branchValues.insert(datas[i][attr.index]);
                valueDataMap[datas[i][attr.index]].push_back(datas[i]);
            }
            double gainAttr=0;
            for (std::map<double, std::vector<LabledVector>>::iterator iter = valueDataMap.begin(); iter!=valueDataMap.end(); iter++)
            {
                gainAttr+=iter->second.size()*informationEntropy(iter->second);
            }
            gainAttr=(dataEnt-gainAttr/datas.size())/intrinsic;
            if (gainAttr>gain)
            {
                gain=gainAttr;
                attrBranchValues=branchValues;
                result=attr;
            }
        }
    }
    result.branchValues=attrBranchValues;
    return result;
}

Attr GiniIndex::operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs)
{
    Attr result;
    double gini=0;
    std::set<double> attrBranchValues;
    for (Attr& attr : attrs)
    {
        if (attr.isContinuos)
        {
            std::set<double> valueset;
            for (unsigned long i = 0; i < datas.size(); ++i)
            {
                valueset.insert(datas[i][attr.index]);
            }
            std::vector<double> branchValues;//binary branch values
            std::set<double>::iterator iter=valueset.begin();
            double prevar=*iter;
            double nextvar;
            for (++iter;iter!=valueset.end(); iter++)
            {
                //build branchValues
                nextvar=*iter;
                branchValues.push_back((prevar+nextvar)/2);
                prevar=nextvar;
            }
            std::map<double, std::vector<LabledVector>> valueDataMap;
            double giniAttr=0;
            double bestBranchValue;
            //select best branch value
            for (std::vector<double>::iterator i = branchValues.begin(); i != branchValues.end(); i++)
            {
                std::vector<LabledVector> smaller;
                std::vector<LabledVector> larger;
                for (std::vector<LabledVector>::iterator j = datas.begin(); j !=datas.end() ; j++)
                {
                    if ((*j)[attr.index]<*i)
                    {
                        smaller.push_back(*j);
                    }else
                    {
                        larger.push_back(*j);
                    }
                }
                double giniBranch=smaller.size()*giniIndex(smaller)+larger.size()*giniIndex(larger);
                giniBranch/=datas.size();
                if (giniBranch>giniAttr)
                {
                    giniAttr=giniBranch;
                    bestBranchValue=*i;
                }
            }
            if (giniAttr>gini)
            {
                gini=giniAttr;
                attrBranchValues.clear();
                attrBranchValues.insert(bestBranchValue);
                result=attr;
            }
        }else
        {
            std::set<double> branchValues;
            std::map<double, std::vector<LabledVector>> valueDataMap;
            for (std::vector<LabledVector>::iterator iter = datas.begin(); iter != datas.end(); iter++)
            {
                valueDataMap[(*iter)[attr.index]].push_back(*iter);
                branchValues.insert((*iter)[attr.index]);
            }
            double attrGini=0;
            for (std::map<double, std::vector<LabledVector>>::iterator iter = valueDataMap.begin(); iter != valueDataMap.end(); iter++)
            {
                attrGini+=iter->second.size()/datas.size()*giniIndex(iter->second);
            }
            if (attrGini>gini)
            {
                result=attr;
                gini=attrGini;
                attrBranchValues=branchValues;
            }
        }
    }
    result.branchValues=attrBranchValues;
    return result;
}

double patrick::informationEntropy(std::vector<LabledVector>& datas)
{
    double result=0;
    std::map<unsigned long, std::vector<LabledVector>> lableDataMap;
    for (std::vector<LabledVector>::iterator iter = datas.begin(); iter != datas.end(); iter++)
    {
        lableDataMap[iter->lable].push_back(*iter);
    }
    for (std::map<unsigned long, std::vector<LabledVector>>::iterator iter = lableDataMap.begin(); iter != lableDataMap.end(); iter++)
    {
        double pLable=(double)iter->second.size()/datas.size();
        result+=pLable*std::log2(pLable);
    }
    return -1*result;
}

double patrick::intrinsicValue(std::vector<LabledVector>& datas, Attr& attr)
{
    double result=0;
    std::map<double, unsigned long> valueAmountMap;
    for (std::vector<LabledVector>::iterator iter = datas.begin(); iter != datas.end(); iter++)
    {
        if (valueAmountMap.count((*iter)[attr.index])==0)
        {
            valueAmountMap[(*iter)[attr.index]]=1;
        }else
        {
            valueAmountMap[(*iter)[attr.index]]++;
        }
    }
    for (std::map<double, unsigned long>::iterator iter = valueAmountMap.begin(); iter != valueAmountMap.end(); iter++)
    {
        double p=(double)iter->second/datas.size();
        result+=p*std::log2(p);
    }
    return -1*result;
}

double patrick::giniIndex(std::vector<LabledVector>& datas)
{
    double result=0;
    std::map<unsigned long, unsigned long> lableDataAmountMap;
    for (std::vector<LabledVector>::iterator iter = datas.begin(); iter != datas.end(); iter++)
    {
        if (lableDataAmountMap.count(iter->lable)==0)
        {
            lableDataAmountMap[iter->lable]=0;
        }else
        {
            lableDataAmountMap[iter->lable]++;
        }
    }
    for (std::map<unsigned long, unsigned long>::iterator iter = lableDataAmountMap.begin(); iter != lableDataAmountMap.end(); iter++)
    {
        result+=std::pow(iter->second/datas.size(), 2);
    }
    return 1-result;
}