#include <iostream>
#include <string>
#include "aho_corasick.hpp"
using namespace std;
int main() {
  const vector<string> pat_vec{"i", "in", "tin", "sting"};
  AC_Tree::Tree ac_tree(pat_vec);
  ac_tree.print(cout);
  ac_tree.plot_tree();
}
