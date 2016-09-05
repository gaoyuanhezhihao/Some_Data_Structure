#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <vector>
#include <iostream>
using namespace std;
template <typename Comparable>
class BinaryHeap
{
public:
    //---function---
    explicit BinaryHeap(int capacity = 100): currentSize(0){
        array.reserve(capacity);
    }
	explicit BinaryHeap(const std::vector<Comparable> & items);
    bool isEmpty() const {
        return 0 == currentSize;
    }
	const Comparable & findMin() const;

    void insert(Comparable const & x);
	void deleteMin();
	void deleteMin( Comparable & minItem);
	void makeEmpty();
    void print();
    //---data---
private:
	int currentSize;
    std::vector<Comparable> array;
    void buildHeap();
    void percolateDown( int hole );
};

template <typename Comparable>
void BinaryHeap<Comparable>::print() {
    int i = 0;
    for(i= 1; i<currentSize+1;++i) {
        cout << array[i] << ", "; 
    }
    cout << endl;
}

//template <typename Comparable>
//bool BinaryHeap<Comparable>::isEmpty() {
    //return 0 == currentSize;
//}

template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & x)
{
    if(currentSize == array.size() - 1 )
        array.resize( array.size() * 2);
    // Percolate up
    int hole = ++ currentSize;
    Comparable copy = x;

    array[0] = std::move( copy );
    /*bubble up.*/
    for(; x< array[hole / 2]; hole /= 2)
        array[ hole  ] = std::move( array[ hole / 2] );
    array[ hole ] = std::move( array[ 0 ] );
}
/**
* Remove the minimum item.
* Throws UnderflowException if empty.
*/
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
    if( isEmpty())
    {
        std::cout << "UnderflowException"<<endl;
    }
    //minItem = std::move( array[ 1 ] );
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
}
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &minItem)
{
    if( isEmpty())
    {
        std::cout << "UnderflowException"<<endl;
    }
    minItem = std::move( array[ 1 ] );
    array[ 1 ] = std::move( array[ currentSize-- ] );
    percolateDown( 1 );
}
/**
*   Internal method to percolate down in the heap.
* hole is the index at which the percolate begins.
*/
template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
    int child = 0;
    Comparable tmp = array[hole];
    for(;hole*2 <=  currentSize;hole = child)
    {
        child = hole * 2;
        //cout << "***" << array[child] << ',' << array[child+1] << endl;
        if(array[child] > array[child+1])
        {
            child++;
        }
        //cout << ".." << array[hole] << ".." << array[child] << endl;
        if(tmp > array[child])
        {
            array[hole] = array[child];
            //cout << "hole:" << hole << ", child" << child << endl;
        }
        else
        {
            break;
        }
    }
    array[hole] = tmp;
}
template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( const vector<Comparable> & items )
    : array(items.size() *2), currentSize( items.size())
{
    size_t i = 0;
    for(i=0;i<items.size();++i) {
        array[i+1] = items[i];
    }
    buildHeap();
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    for( int i = currentSize / 2; i > 0 ; --i)
        percolateDown(i);
}

#endif
