#include <iostream>
#include <fstream>

#include "skew_heap.h"

using namespace std;

int main()
{
    int binary_h1[] = {0, 3, 10, 8, 21, 14, 17, -1, -1, -1, 23, -1, 26, -1};
    int binary_h2[] = {0, 6, 12, 7, 18, 24, 37, 19, -1, -1, 33};
    TreeNode<int> * root_h1 = build_from_bina_heap(binary_h1, sizeof(binary_h1)/sizeof(int), 1);
    TreeNode<int> * root_h2 = build_from_bina_heap(binary_h2, sizeof(binary_h2)/sizeof(int), 1);
    show_heap(root_h1, "h1");
    show_heap(root_h2, "h2");
    root_h1 = merge(root_h1, root_h2);
    show_heap(root_h1, "merged");
    return 0;
}
