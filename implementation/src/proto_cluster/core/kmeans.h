#ifndef CORE_KMEANS_H
#define CORE_KMEANS_H
#include "./../../common/core/cluster.h"
#include "./../../common/core/dist_func.h"
namespace patrick
{
    class KMeans : public Cluster
    {
    private:
        DistanceFunc& distanceFunc;
        unsigned long maxRepeat;
        double minDist;
    public:
        KMeans(unsigned long k, DistanceFunc& dist, unsigned long maxRepeat=100, double minDist=0.1) 
            : Cluster{k}, distanceFunc{dist}, maxRepeat{maxRepeat}, minDist{minDist} {};
        void cluster(double *data, unsigned long width, unsigned long length);
    };
    
} // namespace patrick

#endif