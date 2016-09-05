#include <iostream>
#include <vector>
#include "BinaryHeap.h"
using namespace std;
int main(int argc, char **argv)
{
    std::vector<int> tmp_data{1, 3, 1, 4, 4, 2, 5, 7, 8 , 10 , 6, 2} ;
    //BinaryHeap<int> heap_int(tmp_data);
    BinaryHeap<int> heap_int(100);
    for(auto n:tmp_data) {
        heap_int.insert(n);
    }
    for(auto n:tmp_data) {
        heap_int.deleteMin();
        heap_int.print();
    }
	return 0;
}
