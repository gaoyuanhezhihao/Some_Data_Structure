#ifndef BINARYSEARCH_TREE_HPP
#define BINARYSEARCH_TREE_HPP

#include "BinarySearchTree/Node.hpp"
template <class DATA_TYPE>
class BinaryTree{
    using NODE = TreeNode<DATA_TYPE>;
    public:
        const NODE *insert(const DATA_TYPE &);       
        const NODE *find(const DATA_TYPE & dst);
        const NODE * find_min();
        const NODE * find_max();
        const NODE * remove(const DATA_TYPE & dst);
        BinaryTree()=default;
        ~BinaryTree();
        bool plot_tree(std::string name);
        //void print_down(std::ostream &out_buf, const std::string &relation_sign, const std::string &sep_sign);
    private:
        NODE * root= nullptr;
};

template <class DATA_TYPE>
const TreeNode<DATA_TYPE> * BinaryTree<DATA_TYPE>::insert(const DATA_TYPE & data) {
    if(nullptr != root) {
        return root -> insert(data);
    }else {
        root = new TreeNode<DATA_TYPE> (data);
        return root;
    }
}

template <class DATA_TYPE>
const TreeNode<DATA_TYPE> * BinaryTree<DATA_TYPE>::find(const DATA_TYPE & dst) {
    if(nullptr != root) {
        return root -> find(dst);
    }else {
        return nullptr;
    }
}

template <class DATA_TYPE>
const TreeNode<DATA_TYPE> * BinaryTree<DATA_TYPE>::find_min() {
    if(nullptr != root) {
        return root->find_min();
    }else {
        return nullptr;
    }
}

template <class DATA_TYPE>
bool BinaryTree<DATA_TYPE>::plot_tree(std::string name) {
    if(nullptr == root) {
        return false;
    }else {
        return root->plot_tree(name);
    }
}

template <class DATA_TYPE>
BinaryTree<DATA_TYPE>::~BinaryTree() {
    if(nullptr != root) {
        delete root;
    }
}

template <class DATA_TYPE>
const TreeNode<DATA_TYPE> * BinaryTree<DATA_TYPE>::remove(const DATA_TYPE & dst) {
    if(nullptr == root) {
        return nullptr;
    }else {
        root = root->remove(dst);
    }
}
#endif //BINARYSEARCH_TREE_HPP
