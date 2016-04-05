#include <iostream>
#include "binominal_heap.h"
using namespace std;

int main()
{
    //int i = 1;
    //int * pi = &i, *pi2 = nullptr;
    //cout <<"!! pi=" <<!!pi << ", !!pi2: " <<!!pi2 <<endl;
    int data[10] = {2, 3, 5, 4, 10, 7, 9, 8, 1, 6};
    Bino_Heap<int> b_heap;
    buid_bino_heap(data, 10, b_heap);
    b_heap.show_bino_heap("binary_heap");
    return 0;
}
