#include "mixture_gaussian.h"
#include "./../../common/core/Vector.h"
#include <cmath>
using namespace patrick;
void MixGaussian::cluster(double *data, unsigned long width, unsigned long length)
{
    //collect input data
    std::vector<Vector> datas;
    for (unsigned long i = 0; i < length; i++)
    {
        Vector dataVec{data+i*width, width};
        datas.push_back(dataVec);
    }
    //initialize model parameters
    for (unsigned long i = 0; i < k; i++)
    {
        Matrix unit{width};
        Vector zero{width};
        Gaussian gaussian{width, unit, zero};
        gaussians.push_back(gaussian);
        weights.push_back(1.0/k);
    }
    //iterate to optimize model
    double likely=likelyhood(datas);
    Matrix finalPosterior;
    for (unsigned int iter = 0; iter < maxRepeat; iter++)
    {
        Matrix posterior{length, k};// posterior probability
        for (unsigned long i = 0; i < length; i++)
        {
            double mixture=0;
            for (unsigned long j = 0; j < k; j++)
            {
                double prob=weights[j]*gaussians[j].probability(datas[i]);
                mixture+=prob;
                posterior[i][j]=prob;
            }
            //calculate posterior
            for (unsigned long j = 0; j < k; j++)
            {
                posterior[i][j]/=mixture;
            }
        }
        //update parameters
        for (unsigned long i = 0; i < k; i++)
        {
            double sum=0;
            for (unsigned long j = 0; j < length; j++)
            {
                sum+=posterior[j][i];
            }
            //calculate mu
            Vector muNew{width};
            for (unsigned long j = 0; j < length; j++)
            {
                muNew+=posterior[j][i]*datas[j];
            }
            muNew=1/sum*muNew;
            //calculate sigma
            Matrix sigmaNew{width, width};
            for (unsigned long j = 0; j < length; j++)
            {
                Vector diffVec=datas[j]-muNew;
                Matrix diff{diffVec};
                sigmaNew+=posterior[j][i]*diff*diff.transposition();
            }
            sigmaNew=1/sum*sigmaNew;
            //update parameters
            gaussians[i].setMu(muNew);
            gaussians[i].setSigma(sigmaNew);
            weights[i]=sum/length;
        }
        finalPosterior=posterior;
        //check if stop
        double newLikely=likelyhood(datas);
        if (std::abs(likely-newLikely<minChange))
        {
            break;
        }
        likely=newLikely;
    }

    //cluster
    for (unsigned long i = 0; i < length; i++)
    {
        double posterior=finalPosterior[i][0];
        unsigned long cluster=0;
        for (unsigned long j = 1; j < k; j++)
        {
            if (finalPosterior[i][j]>posterior)
            {
                posterior=finalPosterior[i][j];
                cluster=j;
            }
        }
        clusters[cluster].push_back(datas[i]);
    }
}

double MixGaussian::likelyhood(std::vector<Vector>& datas)
{
    double result=0;
    for (unsigned long i = 0; i < datas.size(); i++)
    {
        double prob=0;
        for (unsigned long j = 1; j < k; j++)
        {
            prob+=weights[j]*gaussians[j].probability(datas[i]);
        }
        result+=std::log(prob);
    }
    return result;
}