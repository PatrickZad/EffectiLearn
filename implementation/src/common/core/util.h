#ifndef CORE_UTIL_H
#define CORE_UTIL_H
#include <vector>
namespace patrick
{
    template<class T>
    unsigned long inversionNum(std::vector<T>& sequence);
    template<class T>
    std::vector<std::vector<T>> allPermutation(std::vector<T>& sequence);
    
    template<class T>
    struct PermutationNode
    {
        T data;
        PermutationNode* parent;
        std::vector<PermutationNode*> nexts;
    };
    template<class T>
    void buildPermutationTree(PermutationNode<T>* root, std::vector<T> leftData, std::vector<PermutationNode<T>*>& leaves);
    template<class T>
    void releaseTree(PermutationNode<T>* root);
} // namespace patrick

#endif // CORE_UTIL_H
