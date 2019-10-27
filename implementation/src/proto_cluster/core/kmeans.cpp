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
    
}