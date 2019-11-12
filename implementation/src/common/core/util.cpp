#include "util.h"
template<class T>
unsigned long patrick::inversionNum(std::vector<T> sequence)
{
    unsigned long result=0;
    unsigned long start=sequence.size()-1;
    for (; start > 0; start--)
    {
        for (unsigned long i = 0; i < start; i++)
        {
            if (sequence[i] > sequence[start])
            {
                result++;
            }
        }
    }
    return result;
}
template<class T>
std::vector<std::vector<T>> patrick::allPermutation(std::vector<T> sequence)
{
    std::vector<std::vector<T>> result;
    PermutationNode<T>* nullRoot=new PermutationNode<T>{sequence[0], nullptr};
    std::vector<PermutationNode<T>*> leaves;
    buildPermutationTree(nullRoot, sequence, leaves);
    for (unsigned long i = 0; i < leaves.size(); ++i) {
        std::vector<T> permutation;
        PermutationNode<T>* next=&leaves[i];
        while (next!=nullRoot)
        {
            permutation.push_back(next->data);
            next=next->parent;
        }
        result.push_back(permutation);
    }
    return result;
}

template<class T>
void patrick::buildPermutationTree(patrick::PermutationNode<T>* root, std::vector<T> leftData, std::vector<PermutationNode<T>*>& leaves)
{
    if (leftData.size()==0)
    {
        leaves.push_back(root);
        return;
    }
    for (unsigned long i = 0; i < leftData.size(); i++)
    {
        PermutationNode<T>* newNode=new PermutationNode<T>{leftData[i], root};
        std::vector<T> newLeft=leftData;//copy
        newLeft.erase(&leftData[i]);
        buildPermutationTree(newNode, newLeft);
        root->nexts.push_back(newNode);
    }
}
template<class T>
void patrick::releaseTree(patrick::PermutationNode<T>* root)
{
    if (root->nexts.size()==0)
    {
        delete root;
    }
    for (unsigned long i = 0; i < root->nexts.size(); i++)
    {
        releaseTree(root->nexts[i]);
    }
    delete root;
}