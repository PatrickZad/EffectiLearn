#ifndef CORE_KDTREE_H
#define CORE_KDTREE_H
#include <vector>
#include "common/core/common.h"
namespace patrick{
    class KDTree
    {
    public:
        KDNode* root;
        long k;
    public:
        KDTree(std::vector<Vector>& data, long k);
        ~KDTree();
        std::vector<Vector> searchNN(Vector& sample);
    private:
        void releaseTree(KDNode* root);
        void buildTree(KDNode* parent,std::vector<Vector>& dataLeft,long dimension);
    };
    struct KDNode
    {
        std::vector<Vector> data;
        KDNode* parent;
        KDNode* left;
        KDNode* right; 
    };
    double getMid(std::vector<Vector>& collection, long dimension);
    long partition(std::vector<Vector>& collection, long start, long end, long dimension);
}

#endif