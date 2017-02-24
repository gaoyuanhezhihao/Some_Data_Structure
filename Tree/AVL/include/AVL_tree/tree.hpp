#ifndef AVL_TREE_TREE_HPP
#define AVL_TREE_TREE_HPP

#include "AVL_tree/node.hpp"
#include <utility>
#include <iostream>
#include <string>
#include <fstream>
template <class T>
class AVLTree{
    using NODE = AVL_TreeNode<T>;
    public:
        const NODE *insert(const T&);
        void print(std::ostream & of);
        void rm_last();
        void rm(const T & data);
        void plot_tree(std::string name);
        //void update_special(NODE* last);
        void plot_min_max(std::fstream &f);

    private:
        NODE * root = nullptr;
        //NODE * _min_ptr= nullptr;
        //NODE * _max_ptr= nullptr;
};

template <class T>
void AVLTree<T>::plot_tree(std::string name){
    const std::string file_name = name + ".dot";
    std::ofstream f(file_name);
    f << "digraph " << name  << "{" << std::endl;
    if(root != nullptr) {
        root->plot_tree(f);
    }
    f << "}" << std::endl;
    std::string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./data/" + name + ".png");
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    return;
}

//template <class T>
//void AVLTree<T>::plot_min_max(std::fstream & f) {
    //if(nullptr != _min_ptr) {
        //f << "min->"<< _min_ptr->get_data() << ";"<< std::endl;
    //}
    //if(nullptr != _min_ptr) {
        //f << "max->"<< _max_ptr->get_data() << ";" <<std::endl;
    //}
    //return;
//}

template <class T>
void AVLTree<T>::rm(const T & data) {
    if(nullptr == root) {
        return;
    }else if(*root == data){
        root = root->rm();
    }else {
        root = root->rm_son(data);
    }

    //if(*_min_ptr == data) {
        //_min_ptr = root->find_min();
    //}
    //if(*_max_ptr == data) {
        //_max_ptr = root->find_max();
    //}
    return;
}

//template <class T>
//void AVLTree<T>::rm_last(){
    //const T & data = _last->get_data();
    //AVL_TreeNode<T> * father_last = _last->get_father();
    //if(nullptr == father_last) {[>last is root<]
        //delete _last;
        //root = nullptr;
    //}else {
        //father_last -> rm_son(data);
    //}
//}

//template <class T>
//void AVLTree<T>::update_special(AVL_TreeNode<T> * last) {
    //if(nullptr == _min_ptr || _min_ptr->get_data() > last->get_data()) {
        //_min_ptr = last;
    //}

    //if(nullptr == _max_ptr || _max_ptr->get_data() < last->get_data()) {
        //_max_ptr = last;
    //}
    //return;
//}
template <class DATA_TYPE>
const AVL_TreeNode<DATA_TYPE> * AVLTree<DATA_TYPE>::insert(const DATA_TYPE & data) {
    if(nullptr != root) {
        root = root -> insert(data);
        //root->set_father(nullptr);
        //update_special(root);
        return root;
    }else {
        root = new AVL_TreeNode<DATA_TYPE> (data);
        //update_special();
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
#endif //AVL_TREE_TREE_HPP
