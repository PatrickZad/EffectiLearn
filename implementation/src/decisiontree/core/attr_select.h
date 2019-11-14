#ifndef CORE_ATTR_SELECT_H
#define CORE_ATTR_SELECT_H
#include <vector>
#include "./../../common/core/Vector.h"
#include <set>
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
    class AttrSelecter
    {
    public:
       virtual Attr operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs)=0;
    };
    
    class InformationGain : public AttrSelecter
    {
    public:
        Attr operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    class GainRatio : public AttrSelecter
    {
    public:
        Attr operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    class GiniIndex : public AttrSelecter
    {
    public:
        Attr operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    double informationEntropy(std::vector<LabledVector>& datas);
    double intrinsicValue(std::vector<LabledVector>& datas, Attr& attr);
    double giniIndex(std::vector<LabledVector>& datas);
} // namespace patrick

#endif