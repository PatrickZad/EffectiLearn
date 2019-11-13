#ifndef CORE_KDTREE_H
#define CORE_KDTREE_H
#include <vector>
#include "./../../common/core/dist_func.h"
#include "./../../common/core/Vector.h"
namespace patrick{
    struct KDNode
    {
        std::vector<LabledVector> data;
        KDNode* parent;
        KDNode* left;
        KDNode* right; 
        unsigned long partitionDim;
    };

    class KDTree
    {
    public:
        KDNode* root;
        DistanceFunc& distFunc;
    public:
        KDTree(DistanceFunc& distFunc);
        //KDTree(std::vector<Vector>& data, DistanceFunc distFunc);
        ~KDTree();

        void setDistFunc(DistanceFunc& distFunc);
        void build(std::vector<LabledVector>& data);
        std::vector<LabledVector> searchNN(Vector& sample, unsigned long k);
    private:
        void releaseTree(KDNode* root);
        void buildTree(KDNode* parent,std::vector<LabledVector>& dataLeft,unsigned long dimension);
    };

    double getMid(std::vector<LabledVector>& collection, unsigned long dimension);
    unsigned long partition(std::vector<LabledVector>& collection, unsigned long start, unsigned long end, unsigned long dimension);
    KDNode* findArea(Vector& sample, KDNode* root);
    
    struct HeapItem
    {
        double distance;
        LabledVector* dataPtr;
    };
    

    class DistanceHeap
    {
    private:
        HeapItem* array;
        unsigned long arrayLength;
        unsigned long dataLength;        
    public:
        DistanceHeap(unsigned long length);
        ~DistanceHeap();

        bool isFull();
        void push(double distance, LabledVector* dataPtr);
        double topDistance();
        std::vector<LabledVector> tovector();
    
    private:
        void heapifyTopDown(unsigned long index);
        void heapifyDownTop(unsigned long index);
    };
    void searchTree(Vector& sample, DistanceFunc& distFunc, KDNode* root, DistanceHeap& heap);

}

#endif