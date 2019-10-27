#ifndef CORE_KMEANS_H
#define CORE_KMEANS_H
#include "./../../common/core/cluster.h"
namespace patrick
{
    class KMeans : public Cluster
    {
    private:
        /* data */
    public:
        KMeans(unsigned long k) : Cluster{k} {};
    };
    
} // namespace patrick

#endif