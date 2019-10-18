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

} // namespace patrick

#endif