#ifndef SPLAYTREE_TREE_H
#define SPLAYTREE_TREE_H

#include "SplayTree/node.h"
#include <iostream>
#include <fstream>
#include <string>

template <class T>
class SplayTree{
    using NODE = SplayTreeNode<T>;
    public:
        const NODE *insert(const T&);
        void print(std::ostream & of);
        NODE * find(const T&);
        bool plot_tree(std::string name);
    private:
        NODE * root = nullptr;
}; 


template <class DATA_TYPE>
const SplayTreeNode<DATA_TYPE> * SplayTree<DATA_TYPE>::insert(const DATA_TYPE & data) {
    if(nullptr != root) {
        return root = root -> insert(data);
    }else {
        root = new SplayTreeNode<DATA_TYPE> (data);
        return root;
    }
}
template <class T>
void SplayTree<T>::print(std::ostream & of) {
    if(nullptr != root)  {
        root -> print_down(of);
    }else{
        return;
    }
}

template <class T>
SplayTreeNode<T> * SplayTree<T>::find(const T & target){
    if(nullptr != root) {
        root = root -> find_root(target);
        return root;
    }else{
        return nullptr;
    }
}
template <class DATA_TYPE> 
bool SplayTree<DATA_TYPE>::plot_tree(std::string name) {
    const std::string file_name = name+ ".dot";
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return false;
    }
    file_stream << "graph " << name<< "{\n";
    root->print_down(file_stream, " -- ", ";\n"); 
    file_stream << "}" << std::endl;
    std::string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+ name+ ".png");
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    return true;
}

#endif //SPLAYTREE_TREE_H
