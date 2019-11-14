#ifndef CORE_ATTR_SELECT_H
#define CORE_ATTR_SELECT_H
#include "decisiontree.h"
#include <vector>
#include "./../../common/core/Vector.h"
namespace patrick
{
    class AttrSelecter
    {
    public:
       virtual Attr& operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs)=0;
    };
    
    class InformationGain : public AttrSelecter
    {
    public:
        Attr& operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    class GainRatio : public AttrSelecter
    {
    public:
        Attr& operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    class GiniIndex : public AttrSelecter
    {
    public:
        Attr& operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs);
    };

    double informationEntropy(std::vector<LabledVector>& datas);
    double intrinsicValue(std::vector<LabledVector>& datas, Attr& attr);
    double giniIndex(std::vector<LabledVector>& datas);
} // namespace patrick

#endif