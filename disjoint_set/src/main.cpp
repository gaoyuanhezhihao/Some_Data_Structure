#include <iostream>
#include <vector>
#include "disjoint_set.h"
using namespace std;
int main(int argc, char **argv)
{
    std::vector<int> tmp_data{1} ;
    DisjointSet test_set(10);
    test_set.SetUnion(7,8);
    test_set.SetUnion(5, 6);
    test_set.SetUnion(6, 7);
    test_set.SetUnion(4, 5);
    test_set.print();
    test_set.plot("test_set");
    test_set.find(8);
    test_set.plot("last");
    test_set.print();
	return 0;
}
