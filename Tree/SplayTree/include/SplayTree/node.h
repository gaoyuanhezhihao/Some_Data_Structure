#ifndef SPLAY_TREE_NODE_H
#define SPLAY_TREE_NODE_H

#include <iostream>

template <class T>
class SplayTreeNode{
    using NODE = SplayTreeNode<T>;
    public:
        NODE* insert(const T&);
        bool operator < (const T&);
        NODE* find_root(const T&);
        void print_down(std::ostream &,
                const std::string & relation_sign=std::string("--"),
                const std::string & sep_sign=std::string(";\n"));
        SplayTreeNode(const T& new_data):data(new_data){}
    private:
        /*function*/
        NODE* find_in_left(const T&, int & deep);
        NODE* find_in_right(const T&, int & deep);
        NODE* rotate_l(const T&);
        NODE* rotate_r(const T&);
        NODE* find(const T&, int & deep);
        /*variable*/
        T data;
        NODE* left=nullptr;
        NODE* right=nullptr;
};
template <class T>
void SplayTreeNode<T>::print_down(std::ostream &of, const std::string & relation_sign, const std::string & sep_sign){
    if(left != nullptr) {
        of << data << relation_sign<< left->data<< sep_sign;
        left -> print_down(of,relation_sign, sep_sign);
    }
    if(right != nullptr) {
        of << data << relation_sign << right -> data << sep_sign;
        right -> print_down(of, relation_sign, sep_sign);
    }
}
template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::rotate_r(const T& target) {
    SplayTreeNode * child = right;
    if(target < child -> data) {
        /*zig-zag mode*/
        SplayTreeNode<T> * grand_child = child -> left; 
        child -> left = grand_child -> right;
        this-> right = grand_child -> left;
        grand_child -> left = this;
        grand_child -> right = child;
        return grand_child;
    }else {
        /*zag-zag mode*/
        SplayTreeNode<T> * grand_child = child -> right;
        child -> right = grand_child -> left;
        grand_child -> left = child;
        right = child->left;
        child->left = this;
        return grand_child;
    }
}
template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::rotate_l(const T& target) {
    SplayTreeNode * child = left;
    if(target > child->data) {
        /*zig-zag mode*/
        SplayTreeNode<T> * grand_child = child -> right;
        child->right = grand_child->left;
        this->left = grand_child -> right; 
        grand_child -> left = child;
        grand_child -> right = this;
        return grand_child;
    }else {
        /*zig-zig mode*/
        SplayTreeNode<T> * grand_child = child -> left;
        child -> left = grand_child -> right;
        grand_child -> right = child;
        left = child->right;
        child->right = this;
        return grand_child;
    }
}

template <class T>
SplayTreeNode<T>* SplayTreeNode<T>::insert(const T& new_data){
    if ( new_data < data) {
        if(nullptr == left) {
            left = new SplayTreeNode<T>(new_data);
        }else{
            left->insert(new_data);
        }
    }else if(data < new_data) {
        if(nullptr == right) {
            right = new SplayTreeNode<T>(new_data);
        }else{
            right -> insert(new_data);
        }
    }
    return this;
}
template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::find(const T& target, int & deep) {
    if(data < target) {
        return find_in_right(target, deep);
    }else if(target < data) {
        return find_in_left(target, deep);
    }else {
        deep = 1;
        return this;
    }
}

template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::find_in_left(const T& target, int & deep) {
    SplayTreeNode<T> * subt_root = this;
    left = left->find(target, deep);
    if(2 == deep) {
        subt_root = rotate_l(target);
        deep = 1;
    }else{
        ++deep;
    }
    return subt_root;
}

template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::find_in_right(const T& target, int & deep) {
    SplayTreeNode<T> * subt_root = this;
    right = right -> find(target, deep);
    if(2 == deep) {
        subt_root = rotate_r(target);
        deep = 1;
    }else {
        ++deep;
    }
    return subt_root;
}

template <class T>
SplayTreeNode<T> * SplayTreeNode<T>::find_root(const T& target) {
    int deep = 0;
    if(data < target) {
        right = right -> find(target, deep);
        if(2 == deep){
            return rotate_r(target);
        }else{
            /* rotate with only child*/
            SplayTreeNode<T> * child = right;
            right = child -> left;
            child -> left = this;
            return child;
        }
    }else if(target < data) {
        left = left -> find(target, deep);
        if(2 == deep) {
            return rotate_l(target);
        }else{
            /* rotate with only child*/
            SplayTreeNode<T> * child = left;
            left = child -> right;
            child -> right = this;
            return child;
        }
    }
}

#endif //SPLAY_TREE_NODE_H
