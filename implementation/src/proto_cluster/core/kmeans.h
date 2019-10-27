#ifndef CORE_KMEANS_H
#define CORE_KMEANS_H
#include "./../../common/core/cluster.h"
#include "./../../common/core/dist_func.h"
namespace patrick
{
    class KMeans : public Cluster
    {
    private:
        DistanceFunc& distance;
    public:
        KMeans(unsigned long k, DistanceFunc& dist) : Cluster{k}, distance{dist}{};
        void cluster(double *data, unsigned long width, unsigned long length);
    };
    
} // namespace patrick

#endif