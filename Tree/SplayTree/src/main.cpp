#include <iostream>
#include <list>
#include <vector>
#include "SplayTree/tree.h"
using namespace std;

template <class T>
T build_a_tree(const vector<int> datas, int numb) {
    cout << "number"  << numb<< endl;
    T tree;
    for(int i = 0; i< numb; ++i) {
        tree.insert(datas[i]);
    }
    return tree;
}

int main()
{
    vector<int> datas;
    for(int i = 32; i>=1; --i) {
        datas.push_back(i );
    }
    auto a_tree=build_a_tree<SplayTree<int> >(datas, datas.size()); 
    cout << "init tree" << endl;
    a_tree.plot_tree("original");
    
    for(int i = 1; i<= 9; ++i) {
        a_tree.find(i);
        a_tree.plot_tree(string("find_") + to_string(i));
    }
    //a_tree.find(1);
    //cout << "after find \"1\"" << endl;
    //a_tree.plot_tree("find_1");

    //a_tree.find(2);
    //cout << "after find \"2\"" << endl;
    //a_tree.plot_tree("find_2");
}

