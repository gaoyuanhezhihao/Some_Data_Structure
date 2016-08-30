#include <iostream>
#include <vector>
#include "BinaryHeap.h"
using namespace std;
int main(int argc, char **argv)
{
    std::vector<int> tmp_data{1} ;
    BinaryHeap<int> heap_int(tmp_data);
    heap_int.deleteMin();
    heap_int.insert(2);
    heap_int.insert(4);
    heap_int.insert(3);
    heap_int.insert(5);
    heap_int.print();
	return 0;
}
