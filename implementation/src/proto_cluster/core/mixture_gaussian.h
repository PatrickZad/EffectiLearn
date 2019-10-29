#ifndef CORE_MIXTURE_GAUSSIAN_H
#define CORE_MIXTURE_GAUSSIAN_H
#include <vector>
#include "./../../common/core/prob_distribution.h"
#include "./../../common/core/cluster.h"
namespace patrick
{
    class MixGaussian : public Cluster
    {
    private:
        std::vector<Gaussian> gaussians;
        std::vector<double> weights;
    public:
        MixGaussian(unsigned long k) : Cluster{k}{};
        void cluster(double *data, unsigned long width, unsigned long length);
    };
} // namespace patrick

#endif