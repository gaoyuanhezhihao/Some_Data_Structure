#include "myHeap.h"

template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & x)
{
    if(currentSize == array.size() - 1 )
        array.resize( array.size() * 2);
    // Percolate up
    int hole = ++ currentSize;
    Comparable copy = x;

    array[0] = std::move( copy );
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
    for(;hole*2 < currentSize;hole = child)
    {
        child = hole * 2;
        if(array[child] < array[child+1])
        {
            child++;
        }
        if(array[hole] > array[child])
        {
            array[hole] = std::move(array[child]);
        }
        else
        {
            break;
        }
    }
    array[hole] = std::move(tmp);
}
template <typename Comparable>
explicit BinaryHeap<Comparable>::BinaryHeap( const vector<Comparable> & items )
    : array( item.size() + 10), currentSize( item.size())
{
    for( int i = 0; i < items.size(); i++)
    {
        array[ i+1 ] = items[ i ];
    }
    buildHeap();
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    for( int i = currentSize / 2; i > 0 ; --i)
        percolateDown(i);
}
