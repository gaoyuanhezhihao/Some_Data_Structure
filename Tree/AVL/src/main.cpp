#include <iostream>
#include <list>
#include "AVL_tree/tree.hpp"
using namespace std;

template <class T>
T build_a_tree(const int datas[], int numb) {
    cout << "number"  << numb<< endl;
    T tree;
    for(int i = 0; i< numb; ++i) {
        tree.insert(datas[i]);
    }
    return tree;
}

int main()
{
    int a[] = {3,2,1,4,5, 6, 7, 16,15,14,13,12,11,10,8,9};
    auto a_tree=build_a_tree<AVLTree<int> >(a, sizeof(a)/sizeof(int)); 
    cout << "build over" << endl;
    a_tree.plot_tree("ori");
    //a_tree.print(cout);
    int data2rm = 5;
    cout << "delete "<<data2rm << ";" << endl;
    a_tree.rm(data2rm);
    a_tree.plot_tree("rm5");

    //a_tree.print(cout);

    data2rm = 6;
    cout << "delete "<<data2rm << ";" << endl;
    a_tree.rm(data2rm);
    //a_tree.print(cout);
    a_tree.plot_tree("rm6");

    //cout << "last =" << AVL_TreeNode<int>::last->get_data() << endl;
    //cout << "min = " << AVL_TreeNode<int>::min_ptr->get_data() << endl;
    //cout << "max = " << AVL_TreeNode<int>::max_ptr->get_data() << endl;
}

