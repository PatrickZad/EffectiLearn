#ifndef CORE_CLUSTER_H
#define CORE_CLUSTER_H
#include <vector>
#include "Vector.h"
namespace patrick
{
    class Cluster
    {
    protected:
        unsigned long k;
        std::vector<std::vector<Vector>> clusters;
    public:
        Cluster(unsigned long k) : k{k}, clusters{k} {};
        virtual void cluster(double *data, unsigned long width, unsigned long length)=0;
    };
    
} // namespace patrick

#endif