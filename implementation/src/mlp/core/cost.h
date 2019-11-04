#ifndef CORE_COST_H
#define CORE_COST_H
#include "./../../common/core/Vector.h"
namespace patrick
{
    class CostFunc
    {
    public:
        virtual double cost(Vector& output)=0;
        virtual Vector derivative(Vector& output)=0;
    };
    
} // namespace patrick

#endif