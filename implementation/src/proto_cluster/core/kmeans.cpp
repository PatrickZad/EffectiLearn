#include "kmeans.h"
#include <cstdlib>
#include <ctime>
#include <set>
using namespace patrick;
void KMeans::cluster(double *data, unsigned long width, unsigned long length)
{
    //convert input
    std::vector<Vector> datas;
    for (unsigned long i = 0; i < length; i++)
    {
        datas.push_back(Vector{data+width*i, width});
    }
    //initialize center samples
    std::vector<Vector> centers;
    std::set<unsigned long> randIndex;
    std::srand(std::time(NULL));
    while (randIndex.size() != k)
    {
        randIndex.insert(std::rand()%datas.size());
    }
    std::set<unsigned long>::iterator iter=randIndex.begin();
    for (; iter != randIndex.end(); iter++)
    {
        centers.push_back(datas[*iter]);
    }
    //iterate
    unsigned long update=k;
    unsigned long repeat=0;
    while (update!=0 && repeat<maxRepeat)
    {
        repeat++;
        update=0;
        std::vector<Vector>::iterator iter=datas.begin();
        //update clusters
        for (unsigned long i = 0; i < k; i++)
        {
            //clear
            clusters[i].clear();
        }
        for (; iter != datas.end(); iter++)
        {
            unsigned long cluster=0;
            double distance=distanceFunc(*iter,centers[0]);
            for (unsigned long i = 1; i < centers.size(); i++)
            {
                double newDist=distanceFunc(*iter, centers[i]);
                if (newDist<distance)
                {
                    distance=newDist;
                    cluster=i;
                }
            }
            //insert
            clusters[cluster].push_back(*iter);
        }
        //update centers
        for (unsigned long i = 0; i < k; i++)
        {
            Vector newCenter{width};
            std::vector<Vector>::iterator iter=clusters[i].begin();
            for ( ; iter != clusters[i].end(); iter++)
            {
                newCenter+=*iter;
            }
            newCenter=newCenter*(1/clusters[i].size());
            if (distanceFunc(newCenter, centers[i])>minDist)
            {
                update++;
                centers[i]=newCenter;
            }
        }
    }
}