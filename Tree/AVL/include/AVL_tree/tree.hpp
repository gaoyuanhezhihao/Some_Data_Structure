#ifndef AVL_TREE_TREE_HPP
#define AVL_TREE_TREE_HPP

#include "AVL_tree/node.hpp"
#include <iostream>
template <class T>
class AVLTree{
    using NODE = AVL_TreeNode<T>;
    public:
        const NODE *insert(const T&);
        void print(std::ostream & of);
    private:
        NODE * root = nullptr;
};
#endif //AVL_TREE_TREE_HPP

template <class DATA_TYPE>
const AVL_TreeNode<DATA_TYPE> * AVLTree<DATA_TYPE>::insert(const DATA_TYPE & data) {
    if(nullptr != root) {
        return root = root -> insert(data);
    }else {
        root = new AVL_TreeNode<DATA_TYPE> (data);
        return root;
    }
}
template <class T>
void AVLTree<T>::print(std::ostream & of) {
    if(nullptr != root)  {
        root -> print_down(of);
    }else{
        return;
    }
}
