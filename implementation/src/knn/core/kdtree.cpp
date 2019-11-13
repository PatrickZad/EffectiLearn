#include "kdtree.h"
#include <cstdlib>
using namespace patrick;

/*
 *Construct KDTree
 *last dimension of a Vector is supposed to be its lable
 */
/*
KDTree::KDTree(std::vector<Vector>& data, DistanceFunc distFunc): distFunc{distFunc}
{
    root=new KDNode{};
    buildTree(root,data,0);
}
*/

KDTree::KDTree(DistanceFunc& distFunc):distFunc{distFunc}
{
    root=new KDNode{std::vector<LabledVector>{}, nullptr, nullptr, nullptr, 0};
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

void KDTree::build(std::vector<LabledVector>& data)
{
    buildTree(root, data, 0);
}

std::vector<LabledVector> KDTree::searchNN(Vector& sample, unsigned long k){
    DistanceHeap heap{k};
    searchTree(sample,distFunc, root, heap);
    return heap.tovector();
}

void KDTree::buildTree(KDNode* parent,std::vector<LabledVector>& dataLeft,unsigned long depth)
{
    if (dataLeft.size()==0)
    {
        return;
    }
    
    std::vector<LabledVector> left{};
    std::vector<LabledVector> right{};
    unsigned long dimension=depth%(dataLeft[0].size());
    parent->partitionDim=dimension;
    double mid=getMid(dataLeft,dimension);
    for (LabledVector vec : dataLeft)
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
        leftNode->parent=parent;
        buildTree(leftNode,left,depth+1);
    }
    if (right.size()>0)
    {
        KDNode* rightNode=new KDNode{};
        parent->right=rightNode;
        rightNode->parent=parent;
        buildTree(rightNode,right,depth+1);
    }
}

double patrick::getMid(std::vector<LabledVector>& collection, unsigned long dimension)
{
    unsigned long start=0;
    unsigned long end=collection.size()-1;
    unsigned long expect=collection.size()/2;
    unsigned long partitioned=patrick::partition(collection,start,end,dimension);
    while (partitioned!=expect)
    {
        if (partitioned>expect)
        {
            end=partitioned-1;
        }else
        {
            start=partitioned+1;
        }
        partitioned=patrick::partition(collection,start,end,dimension);
    }
    return collection[expect][dimension];
}

unsigned long patrick::partition(std::vector<LabledVector>& collection, unsigned long start, unsigned long end, unsigned long dimension)
{
    if (start==end)
    {
        return start;
    }
    unsigned long randIndex=start+std::rand()%(end-start+1);
    LabledVector temp=collection[start];
    collection[start]=collection[randIndex];
    collection[randIndex]=temp;
    unsigned long left=start+1;
    unsigned long right=end;
    while (left<=right)
    {
        while (left<=right && collection[left][dimension]<=collection[start][dimension])
        {
            left++;
        }
        while (right>=left && collection[right][dimension]>collection[start][dimension])
        {
            right--;
        }
        if (left<right)
        {
            temp=collection[left];
            collection[left]=collection[right];
            collection[right]=temp;
            left++;
            right--;
        }
    }
    temp=collection[left-1];
    collection[left-1]=collection[start];
    collection[start]=temp;
    return left-1;
}

KDNode* patrick::findArea(Vector& sample, KDNode* root){
    KDNode* area=root;
    KDNode* nextArea=root;
    while (nextArea!=nullptr)
    {
        area=nextArea;
        unsigned long dim=area->partitionDim;
        if (sample[dim]<area->data[0][dim])
        {
            nextArea=area->left;
        }else{
            nextArea=area->right;
        }
    }
    return area;
}

void patrick::searchTree(Vector& sample, DistanceFunc& distFunc, KDNode* root, DistanceHeap& heap)
{
    if (root==nullptr)
    {
        return;
    }
    
    KDNode* area=findArea(sample,root);
    for (unsigned long i=0 ; i<area->data.size();i++)
    {
        double distance=distFunc(area->data[i],sample);
        if (heap.topDistance()>distance || !heap.isFull())
        {
            heap.push(distance,&(area->data[i]));
        }
    }
    if (area->left!=nullptr)
    {
        searchTree(sample, distFunc, area->left, heap);
    }
    else if (area->right != nullptr)
    {
        searchTree(sample, distFunc, area->right, heap);
    }
    
    while (area != root)
    {
        area=area->parent;
        double distSampleToPartdim=std::abs(sample[area->partitionDim]-area->data[0][area->partitionDim]);
        if (distSampleToPartdim<heap.topDistance() || !heap.isFull())
        {
            searchTree(sample,distFunc,(area==area->left) ? area->left : area->right,heap);
        }else
            if (distSampleToPartdim==heap.topDistance())
            {
                for (LabledVector data : area->data)
                {
                    double distance=distFunc(data,sample);
                    if (heap.topDistance()>distance || !heap.isFull())
                    {
                        heap.push(distance,&data);
                    }
                }
            }
    }
}

DistanceHeap::DistanceHeap(unsigned long length):dataLength{0}, arrayLength{length}
{
    array=new  HeapItem[length];
    for (unsigned long i = 0; i < length; i++)
    {
        (array+i)->distance=-1;
        (array+i)->dataPtr=nullptr;
    }
}
    
DistanceHeap::~DistanceHeap()
{
    delete[] array;
    array=nullptr;
    dataLength=0;
    arrayLength=0;
}

bool DistanceHeap::isFull()
{
    return arrayLength==dataLength;
}

void DistanceHeap::push(double distance, LabledVector* dataPtr)
{
    HeapItem item{distance,dataPtr};
    if (dataLength<arrayLength)
    {
        *(array+dataLength)=item;
        dataLength++;
        heapifyDownTop(dataLength-1);
    }else{
        *array=item;
        heapifyTopDown(0);
    }
}

double DistanceHeap::topDistance()
{
    return array[0].distance;
}

std::vector<LabledVector> DistanceHeap::tovector()
{
    std::vector<LabledVector> vec{};
    for (unsigned long i = 0; i < dataLength; i++)
    {
        vec.push_back(*(array[i].dataPtr));
    }
    return vec;
}

void DistanceHeap::heapifyTopDown(unsigned long index)
{
    unsigned long largest=index;
    unsigned long left=index*2+1;
    unsigned long right=2*(index+1);
    if (left<dataLength && (array+left)->distance>(array+index)->distance)
    {
        largest=left;
    }
    if (right<dataLength && (array+right)->distance>(array+largest)->distance)
    {
        largest=right;
    }
    if (largest!=index){
        auto temp=array[index];
        array[index]=array[largest];
        array[largest]=temp;
        heapifyTopDown(largest);
    }
}

void DistanceHeap::heapifyDownTop(unsigned long index)
{
    unsigned long i=index;
    while (i>0 && (array+i)->distance>(array+(i-1)/2)->distance){
        HeapItem temp=*(array+(i-1)/2);
        *(array+(i-1)/2)=*(array+i);
        *(array+i)=temp;
        i=(i-1)/2;
    }
}
        