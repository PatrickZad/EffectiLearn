#ifndef CORE_KERNEL_FUNCTION_H
#define CORE_KERNEL_FUNCTION_H
#include "Vector.h"
namespace patrick
{
    class KernelFunction
    {
    public:
        virtual double operator()(Vector& vec0, Vector& vec1)=0;
    };

    class PolynomialKernel : public KernelFunction
    {
    private:
        unsigned int pow;
    public:
        PolynomialKernel(unsigned int pow=3) : pow{pow} {};
        double operator()(Vector& vec0, Vector& vec1);
    };

    class GaussianKernel : public KernelFunction
    {
    private:
        double sigma_square;
    public:
        GaussianKernel(double sigma=1) : sigma_square{sigma*sigma} {};
        double operator()(Vector& vec0, Vector& vec1);
    };
} // namespace patrick

#endif