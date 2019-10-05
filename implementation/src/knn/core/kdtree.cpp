#include "kdtree.h"
#include <cstdlib>
using namespace patrick;

/*
 *Construct KDTree
 */
KDTree::KDTree(std::vector<Vector>& data, long k)
{
    this->k=k;
    root=new KDNode{};
    buildTree(root,data,0);
}

KDTree::~KDTree()
{
    releaseTree(root);
}

void KDTree::releaseTree(KDNode* root)
{
    if (root->left!=nullptr)
    {
        releaseTree(root->left);
    }
    if (root->right!=nullptr)
    {
        releaseTree(root->right);
    }
    delete root;
}

std::vector<Vector> KDTree::searchNN(Vector& sample){
    //TODO
}

void KDTree::buildTree(KDNode* parent,std::vector<Vector>& dataLeft,long depth)
{
    std::vector<Vector> left{};
    std::vector<Vector> right{};
    long dimension=depth%k;
    double mid=getMid(dataLeft,dimension);
    for (Vector vec : dataLeft)
    {
        if (vec[dimension]>mid)
        {
            right.push_back(vec);
        }else
            if (vec[dimension]<mid)
            {
                left.push_back(vec);
            }else
            {
                parent->data.push_back(vec);
            }
    }
    if (left.size()>0)
    {
        KDNode* leftNode=new KDNode{};
        parent->left=leftNode;
        buildTree(leftNode,left,depth++);
    }
    if (right.size()>0)
    {
        KDNode* rightNode=new KDNode{};
        parent->right=rightNode;
        buildTree(rightNode,right,depth++);
    }
}

double patrick::getMid(std::vector<Vector>& collection, long dimension)
{
    long start=0;
    long end=collection.size();
    long expect=collection.size()/2;
    long partitioned=partition(collection,start,end,dimension);
    while (partitioned!=expect)
    {
        if (partitioned>expect)
        {
            end=partitioned;
        }else
        {
            start=partitioned;
        }
        partitioned=partition(collection,start,end,dimension);
    }
    return collection[expect][dimension];
}

long patrick::partition(std::vector<Vector>& collection, long start, long end, long dimension)
{
    if (start==end)
    {
        return start;
    }
    long randIndex=std::rand()%(end-start);
    Vector temp=collection[start];
    collection[start]=collection[randIndex];
    collection[randIndex]=temp;
    long left=start+1;
    long right=end;
    while (left<=end)
    {
        while (collection[left][dimension]<=collection[start][dimension])
        {
            left++;
        }
        while (collection[right][dimension]>collection[start][dimension])
        {
            right--;
        }
        if (left<right)
        {
            temp=collection[left];
            collection[left]=collection[right];
            collection[right]=temp;
        }
    }
    temp=collection[left-1];
    collection[left-1]=collection[start];
    collection[start]=temp;
    return left-1;
}


