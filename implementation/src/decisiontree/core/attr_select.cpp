#include "attr_select.h"
#include <set>
using namespace patrick;
Attr InformationGain::operator()(std::vector<LabledVector> &datas, std::vector<Attr> &attrs)
{
    //common constant will not be calculated
    Attr result;
    double gain=-1;
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

        }
    }
}

Attr GainRatio::operator()(std::vector<LabledVector>& datas, std::vector<Attr>& attrs)
{

}

double patrick::informationEntropy(std::vector<LabledVector>& datas)
{

}