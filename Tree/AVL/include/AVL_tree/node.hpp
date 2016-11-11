#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP
#include <iostream>

template <class DATA_TYPE>
class AVL_TreeNode{
    using AVLNODE = AVL_TreeNode<DATA_TYPE>;
    public:
        AVLNODE* insert(const DATA_TYPE &);
        int get_height();
        AVL_TreeNode(const DATA_TYPE &new_data):element(new_data){}
        bool operator<(const DATA_TYPE& cmp);
        void print_down(std::ostream &);
    private:
        /*function*/
        AVLNODE* single_rotate_l();
        AVLNODE* single_rotate_r();
        AVLNODE* double_rotate_l();
        AVLNODE* double_rotate_r();
        void update_height();
        /*variable*/
        int height=0;
        DATA_TYPE element;
        AVLNODE * left = nullptr;
        AVLNODE * right = nullptr;
};

template <class T>
bool AVL_TreeNode<T>::operator<(const T & cmp) {
    return element < cmp;
}

template <class T>
void AVL_TreeNode<T>::print_down(std::ostream & of) {
    if(left != nullptr) {
        of << element << "-->"<< left->element<< std::endl;
        left -> print_down(of);
    }
    if(right != nullptr) {
        of << element << "-->" << right -> element << std::endl;
        right -> print_down(of);
    }
}
template <class DATA_TYPE>
int AVL_TreeNode<DATA_TYPE>::get_height() {
    if(nullptr == this) {
        return -1;
    }else{
        return height;
    }
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::insert(const DATA_TYPE& new_data) {
    decltype(this) new_root;
    if( new_data < element ) {
        if(nullptr == left) {
            left = new AVL_TreeNode<DATA_TYPE>(new_data);
        }else {
            left = left->insert(new_data);
            if(left->get_height() - right->get_height() == 2){
                if(*(left) < new_data) {
                    return double_rotate_l();
                }else {
                    return single_rotate_l();
                }
            }

        }
    }else if(new_data > element) {
        if(nullptr == right) {
            right = new AVL_TreeNode<DATA_TYPE>(new_data);
        }else {
            right = right->insert(new_data);
            if(right->get_height() - left->get_height() == 2) {
                if(*(right) < new_data) {
                    return single_rotate_r();
                }else {
                    return double_rotate_r();
                }
            }
        }
    }else{
        ; // already existed.
    }
    update_height();
    return this;
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::single_rotate_l() {
    AVL_TreeNode<DATA_TYPE> * old_root = this; 
    AVL_TreeNode<DATA_TYPE> * new_root = old_root->left;
    old_root -> left = new_root->right;
    new_root -> right = old_root;
    old_root -> update_height();
    new_root -> update_height();
    return new_root;
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::single_rotate_r() {
    AVL_TreeNode<DATA_TYPE> * old_root = this;
    AVL_TreeNode<DATA_TYPE> * new_root = old_root->right;
    old_root -> right = new_root ->left; 
    new_root -> left = old_root;
    old_root -> update_height();
    new_root -> update_height();
    return new_root;
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::double_rotate_l() {
    this -> left = left->single_rotate_r();
    return single_rotate_l();
}
template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::double_rotate_r() {
    right = right->single_rotate_l();
    return single_rotate_r();
}

template <class DATA_TYPE>
void AVL_TreeNode<DATA_TYPE>::update_height() {
    int l_height = left == nullptr ? -1: left->height;
    int r_height = right == nullptr? -1: right->height;
    height = std::max(l_height, r_height) + 1;
}
#endif //AVL_NODE_HPP
