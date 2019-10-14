#ifndef CORE_KDTREE_H
#define CORE_KDTREE_H
#include <vector>
#include "common/core/common.h"
#include "common/core/Vector.h"
namespace patrick{
    class KDTree
    {
    public:
        KDNode* root;
        DistanceFunc& distFunc;
    public:
        KDTree(DistanceFunc& distFunc);
        KDTree();
        //KDTree(std::vector<Vector>& data, DistanceFunc distFunc);
        ~KDTree();

        void setDistFunc(DistanceFunc& distFunc);
        void build(std::vector<Vector>& data);
        std::vector<Vector> searchNN(Vector& sample, unsigned long k);
    private:
        void releaseTree(KDNode* root);
        void buildTree(KDNode* parent,std::vector<Vector>& dataLeft,unsigned long dimension);
    };
    struct KDNode
    {
        std::vector<Vector> data;
        KDNode* parent;
        KDNode* left;
        KDNode* right; 
        unsigned long partitionDim;
    };

    double getMid(std::vector<Vector>& collection, unsigned long dimension);
    unsigned long partition(std::vector<Vector>& collection, unsigned long start, unsigned long end, unsigned long dimension);
    KDNode* findArea(Vector& sample, KDNode* root);
    void searchTree(Vector& sample, DistanceFunc distFunc, KDNode* root, DistanceHeap& heap);

    struct HeapItem
    {
        double distance;
        Vector* dataPtr;
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

        void push(double distance, Vector* dataPtr);
        double topDistance();
        std::vector<Vector> tovector();
    
    private:
        void heapifyTopDown(unsigned long index);
        void heapifyDownTop(unsigned long index);
    };
    
    
    
}

#endif