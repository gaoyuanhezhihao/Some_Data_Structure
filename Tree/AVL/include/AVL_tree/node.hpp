#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP
#include <iostream>
#include <fstream>

template <class DATA_TYPE>
class AVL_TreeNode{
    using AVLNODE = AVL_TreeNode<DATA_TYPE>;
    public:
        AVLNODE* insert(const DATA_TYPE &);
        int get_height();
        AVL_TreeNode(const DATA_TYPE &new_data):element(new_data){}
        bool operator<(const DATA_TYPE& cmp);
        bool operator==(const DATA_TYPE& cmpor);
        void print_down(std::ostream &);
        void plot_tree(std::ofstream & f);
        //void set_father(AVL_TreeNode * new_father) {_father = new_father;}
        DATA_TYPE & get_data();
        //DATA_TYPE * get_father(){return _father;}
        //void rm_son(const DATA_TYPE & data);
        AVLNODE* rm_son(const DATA_TYPE & data);
        AVLNODE* rm();
        AVLNODE* find_min();
        AVLNODE* find_max();
    private:
        /*function*/
        //AVLNODE* update_last(AVLNODE * new_last);
        void plot_null_node(std::ofstream & f);
        //void //IamYourFather(); 
        AVLNODE* single_rotate_l();
        AVLNODE* single_rotate_r();
        AVLNODE* double_rotate_l();
        AVLNODE* double_rotate_r();
        void update_height();
        AVLNODE* check_l_bigger();
        AVLNODE* check_r_bigger();
        /*variable*/
        int height=0;
        DATA_TYPE element;
        AVLNODE * left = nullptr;
        AVLNODE * right = nullptr;
        //AVLNODE * _father = nullptr;
};






template<class T>
AVL_TreeNode<T>* AVL_TreeNode<T>::find_max(){
    if(nullptr == right) {
        return this;
    }else {
        return right->find_max();
    }
}

template<class T>
AVL_TreeNode<T>* AVL_TreeNode<T>::find_min(){
    if(nullptr == left) {
        return this;
    }else {
        return left->find_min();
    }

    //if(nullptr == right) {
        //return this;
    //}else {
        //return right->find_min();
    //}
}

template<class T>
AVL_TreeNode<T>* AVL_TreeNode<T>::rm(){
    if(left != nullptr && right != nullptr) {
        AVL_TreeNode<T> * p_right_min_node = right->find_min();
        this->element = p_right_min_node -> element;
        if(p_right_min_node == right) {
            right = right->rm();
        }else{
            right = right->rm_son(element);
        }
        //IamYourFather();
        return check_l_bigger();
    }else if(nullptr == left) {
        AVL_TreeNode<T> * new_root = right;
        this->right = nullptr;
        delete this;
        return new_root;
    }else if(nullptr == right) {
        AVL_TreeNode<T> * new_root = left;
        this->left = nullptr;
        delete this;
        return new_root;
    }
}

template <class T>
AVL_TreeNode<T>*  AVL_TreeNode<T>::rm_son(const T& data) {
    if(data < element) { // in left sub-tree.
        if(data == left->element) {
            left = left->rm();
        }else {
            left = left->rm_son(data);
        }
        //IamYourFather();
        return check_r_bigger();
    }else {// in right sub-tree.
        if(data == right->element){
            right = right->rm();
        }else {
            right = right->rm_son(data);
        }
        //IamYourFather();
        return check_l_bigger();
    }
}

template <class T>
AVL_TreeNode<T> * AVL_TreeNode<T>::check_r_bigger() {
    update_height();
    if(right->get_height() - left->get_height() == 2) {
        AVL_TreeNode<T> * rr = right->right;
        AVL_TreeNode<T> * rl = right->left;
        if(rr->get_height() < rl->get_height()){
            return double_rotate_r();
        }else{
            return single_rotate_l();
        }
    }else {
        return this;
    }
}

template <class T>
AVL_TreeNode<T> * AVL_TreeNode<T>::check_l_bigger() {
    update_height();
    if(left->get_height() - right->get_height() == 2) {
        AVL_TreeNode<T> * ll = left->left;
        AVL_TreeNode<T> * lr = left->right;
        if(ll->get_height() < lr->get_height()) {
            return double_rotate_l();
        }else {
            return single_rotate_l();
        }
    }else {
        return this;
    }
}
//template <class T>
//AVL_TreeNode<T> *AVL_TreeNode<T>::check_left_bigger(){
//if(left->get_height() - right->get_height() == 2){
//if(*(left) < new_data) {
//return double_rotate_l();
//}else {
//return single_rotate_l();
//}
//}
//}

//template<class T>
//void AVL_TreeNode<T>::rm_son(const DATA_TYPE & data) {
//if(data < element) {
//AVL_TreeNode<T> * grandson_l = left->left;
//AVL_TreeNode<T> * grandson_r = left->right;
//delete left;
//[>TODO how to balance after remove ?<]
////left = nullptr;
//}else {
//delete right;
////right = nullptr;
//}
//}

template<class T>
T& AVL_TreeNode<T>::get_data(){
    return element;
}

//template<class T>
//AVL_TreeNode<T> * AVL_TreeNode<T>::min_ptr = nullptr;

//template<class T>
//AVL_TreeNode<T> * AVL_TreeNode<T>::max_ptr = nullptr;

//template<class T>
//AVL_TreeNode<T> * AVL_TreeNode<T>::last = nullptr;

template <class T>
bool AVL_TreeNode<T>::operator<(const T & cmp) {
    return element < cmp;
}
template <class T>
bool AVL_TreeNode<T>::operator==(const T & cmpor) {
    return element == cmpor;
}

template<class T>
void AVL_TreeNode<T>::plot_null_node(std::ofstream &f) {
        f << long(this) << "[style=invis];"<< std::endl;
        f << element << "->" << long(this) << "[style=invis];" << std::endl;
        f << long(this)<< "->" << element  << "[style=invis];" << std::endl;
}

template<class T>
void AVL_TreeNode<T>::plot_tree(std::ofstream & f) {
    //if(nullptr != _father) {
        //f << element  << "->" << _father->element<< " [style=dotted];"<< std::endl;
    //}
    if(nullptr != left) {
        f << element << "->" << left -> element << ";" << std::endl;
        left->plot_tree(f);
    }else{
        plot_null_node(f);
    }
    if(nullptr != right) {
        f << element << "->" << right -> element << ";" << std::endl;
        right -> plot_tree(f);
    }else {
        plot_null_node(f);
    }
    return;
}
template <class T>
void AVL_TreeNode<T>::print_down(std::ostream & of) {
    //if(nullptr == _father) {
        //of << element << "<-- null"  << std::endl;
    //}else {
        //of << element << "<--" << _father->element << std::endl;
    //}

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

//template <class T>
//AVL_TreeNode<T>* AVL_TreeNode<T>::update_last(AVL_TreeNode<T> * new_last) {
    //last = new_last;
    //const T & new_data= last->element;
    //if(nullptr == max_ptr || max_ptr->element < new_data) {
        //max_ptr = last;
    //}
    //if(nullptr == min_ptr || min_ptr->element > new_data) {
        //min_ptr = last;
    //}
//}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::insert(const DATA_TYPE& new_data) {
    decltype(this) new_root;
    if( new_data < element ) {
        if(nullptr == left) {
            left = new AVL_TreeNode<DATA_TYPE>(new_data);
            //update_last(left);
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
    }else{
        if(nullptr == right) {
            right = new AVL_TreeNode<DATA_TYPE>(new_data);
            //update_last(right);
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
    }/*else{*/
    //; // already existed.
    /*}*/
    update_height();
    //IamYourFather();
    return this;
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::single_rotate_l() {
    AVL_TreeNode<DATA_TYPE> * old_root = this; 
    AVL_TreeNode<DATA_TYPE> * new_root = old_root->left;
    old_root -> left = new_root->right;
    //old_root -> IamYourFather();
    new_root -> right = old_root;
    //new_root -> IamYourFather();
    old_root -> update_height();
    new_root -> update_height();
    return new_root;
}

//template <class T>
//void AVL_TreeNode<T>::IamYourFather() {
    //if(nullptr != left) {
        //left->_father = this;
    //}
    //if(nullptr != right) {
        //right -> _father = this;
    //}
//}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::single_rotate_r() {
    AVL_TreeNode<DATA_TYPE> * old_root = this;
    AVL_TreeNode<DATA_TYPE> * new_root = old_root->right;
    old_root -> right = new_root ->left; 
    //old_root -> IamYourFather();
    new_root -> left = old_root;
    //new_root -> IamYourFather();
    old_root -> update_height();
    new_root -> update_height();
    return new_root;
}

template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::double_rotate_l() {
    left = left->single_rotate_r();
    //IamYourFather();
    return single_rotate_l();
}
template <class DATA_TYPE>
AVL_TreeNode<DATA_TYPE>* AVL_TreeNode<DATA_TYPE>::double_rotate_r() {
    right = right->single_rotate_l();
    //IamYourFather();
    return single_rotate_r();
}

template <class DATA_TYPE>
void AVL_TreeNode<DATA_TYPE>::update_height() {
    int l_height = left == nullptr ? -1: left->height;
    int r_height = right == nullptr? -1: right->height;
    height = std::max(l_height, r_height) + 1;
}
#endif //AVL_NODE_HPP
