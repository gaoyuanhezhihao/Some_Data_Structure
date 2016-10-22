#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <utility>
#include <string>
#include <fstream>
#include <iostream>




template <class DATA_TYPE>
class TreeNode{
    using NODE = TreeNode<DATA_TYPE>;
    public:
        NODE *insert(const DATA_TYPE &);       
        NODE *find(const DATA_TYPE & dst);
        NODE * find_min();
        NODE * find_max();
        NODE * remove(const DATA_TYPE & dst);
        TreeNode(const DATA_TYPE &data): element(data){}
        TreeNode(TreeNode && tmp): element(std::move(tmp.element)), left(tmp.left), right(tmp.right){}
        ~TreeNode();
        bool plot_tree(std::string name);
        void print_down(std::ostream &out_buf, const std::string &relation_sign, const std::string &sep_sign);
    private:
        bool make_empty();
        NODE * insert_left(const DATA_TYPE &);
        NODE * insert_right(const DATA_TYPE &);
        DATA_TYPE element;
        NODE * left = nullptr;
        NODE * right = nullptr;
};

template <class DATA_TYPE>
TreeNode<DATA_TYPE>* TreeNode<DATA_TYPE>::remove(const DATA_TYPE &dst) {
    if(dst < this->element) {
        /*search the left side*/
        if(nullptr == left) {
            return this;// can not find it
        }else {
            left = left->remove(dst);
            return this;
        }
    }else if(this -> element < dst) {
        /*search the right side*/
        if(nullptr == right) {
            return this;
        }else {
            right = right -> remove(dst);
            return this;
        }
    }else {
        /*this is the node to be removed*/
        if(left != nullptr && right != nullptr) {
            auto p_right_min_node = right ->find_min();
            this->element = p_right_min_node -> element;
            right->remove(element);
            return this;
        }else if(left == nullptr) {
            /*only right child*/

            auto new_sub_root = right;
            this->right = nullptr;
            delete this;
            return new_sub_root;
        }else if(right == nullptr) {
            /*only left child*/
            auto new_sub_root = left;
            this->left = nullptr;
            delete this;
            return new_sub_root;
        }else {
            /*no child*/
            delete this;
            return nullptr;
        }
    }
}

template <class DATA_TYPE>
void TreeNode<DATA_TYPE>::print_down(std::ostream &out_buf, const std::string &relation_sign, const std::string &sep_sign) {
    if(nullptr != this->left){
        out_buf<<this->element << relation_sign << this->left->element << sep_sign;
        std::cout << "left" <<this->element << relation_sign << this->left->element << sep_sign;
        this->left->print_down(out_buf, relation_sign, sep_sign);
    }
    if(nullptr != this->right) {
        out_buf << this->element << relation_sign << this->right->element << sep_sign;
        std::cout << "right"<<this->element << relation_sign << this->right->element << sep_sign;
        this->right->print_down(out_buf, relation_sign, sep_sign);
    }
    return ;
}

template <class DATA_TYPE> 
bool TreeNode<DATA_TYPE>::plot_tree(std::string name) {
    const std::string file_name = name+ ".dot";
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return false;
    }
    file_stream << "graph " << name<< "{\n";
    print_down(file_stream, " -- ", ";\n"); 
    file_stream << "}" << std::endl;
    std::string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+ name+ ".png");
    std::cout << cmd << std::endl;
    system(cmd.c_str());
    return true;
}

template <class DATA_TYPE>
TreeNode<DATA_TYPE> * TreeNode<DATA_TYPE>::insert(const DATA_TYPE & data) {
    if(this->element == data) {
        return this;
    }else if(this->element > data) {
        return insert_left(data);
    }else{
        return insert_right(data);
    }
}

template <class DATA_TYPE>
TreeNode<DATA_TYPE> * TreeNode<DATA_TYPE>::insert_right(const DATA_TYPE &data) {
    if(this->right != nullptr) {
        return right->insert(data);
    }else {
        right = new TreeNode(data);
    }
}

template <class DATA_TYPE>
TreeNode<DATA_TYPE> * TreeNode<DATA_TYPE>::insert_left(const DATA_TYPE & data) {
    if(this->left != nullptr) {
        return left->insert(data);
    } else {
        /*left subtree is null*/
        left = new TreeNode(data);
    }

}


template <class DATA_TYPE> 
TreeNode<DATA_TYPE>::~TreeNode() {
    if(nullptr != left) {
        delete left;
    }

    if(nullptr != right) {
        delete right;
    }
}

template <class DATA_TYPE>
bool TreeNode<DATA_TYPE>::make_empty(){
    if(nullptr != left) {
        left -> make_empty();
        delete left;
    }

    if(nullptr != right) {
        right -> make_empty();
        delete right;
    }
}
template <class DATA_TYPE>
TreeNode<DATA_TYPE> * TreeNode<DATA_TYPE>::find_min() {
    if(nullptr != left) {
        return left -> find_min();
    }else {
        return this;
    }
}

template <class DATA_TYPE>
TreeNode<DATA_TYPE> * TreeNode<DATA_TYPE>::find(const DATA_TYPE & dst) {
    if(this->element == dst) {
        return this;
    }else if(this->element > dst) {
        /*search down the left sub tree.*/
        if(nullptr != left) {
            return left->find(dst);
        }else {
            return nullptr;
        }
    }else {
        /*search down the right sub tree.*/
        if(nullptr != right) {
            return right -> find(dst);
        }else {
            return nullptr;
        }
    }
}

#endif //BINARYSEARCHTREE_HPP

