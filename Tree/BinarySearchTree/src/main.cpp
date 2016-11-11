#include <iostream>
#include <list>
#include "BinarySearchTree/Tree.hpp"
using namespace std;
BinaryTree<int> build_a_tree(const int datas[], int numb);

int main()
{
    int a[] = {2,3,4,9,8, 5, 10, 19, 1};
    BinaryTree<int> a_tree=build_a_tree(a, sizeof(a)/sizeof(int)); 
    a_tree.plot_tree("a_tree");
    a_tree.remove(4);
    a_tree.plot_tree("a_tree_after_remove");
}

BinaryTree<int> build_a_tree(const int datas[], int numb) {
    cout << "number"  << numb<< endl;
    BinaryTree<int> tree;
    for(int i = 0; i< numb; ++i) {
        tree.insert(datas[i]);
    }
    return tree;
}
