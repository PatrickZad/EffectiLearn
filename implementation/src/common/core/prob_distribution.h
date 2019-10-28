#ifndef CORE_PROB_DISTRIBUTION_H
#define CORE_PROB_DISTRIBUTION_H
#include "Matrix.h"
#include "Vector.h"
namespace patrick
{
    template<class T>
    class Distribution
    {
    public:
        virtual double probability(T& sample)=0;
    };

    class Gaussian : public Distribution<Vector>
    {
    private:
        unsigned long dim;
        Matrix sigma;
        Matrix mu;
        Matrix inverse;
        double denominator;
    public:
        Gaussian(unsigned long dim, Matrix& sigma, Vector& mu);
        double probability(Vector& sample);
    };
    
} // namespace patrick
#endif
