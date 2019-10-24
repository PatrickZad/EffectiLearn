#ifndef CORE_DISTFUNC_H
#define CORE_DISTFUNC_H
#include "Vector.h"
namespace patrick
{
    class DistanceFunc
    {
    public:
        virtual double operator()(Vector& vec0, Vector& vec1)=0;
    };

    class MinkowskiDist : DistanceFunc
    {
    protected:
        unsigned long pow;
    public:
        MinkowskiDist(unsigned long pow);
        double operator()(Vector& vec0, Vector& vec1);
    };

    class EuclideanDist : public MinkowskiDist
    {
    public:
        EuclideanDist() : MinkowskiDist{2} {};
    };

    class ManhattanDist : public MinkowskiDist
    {
    public:
        ManhattanDist() : MinkowskiDist{1} {};
    };

    
} // namespace patrick

#endif