#ifndef MIN_SP_TREE_H
#define MIN_SP_TREE_H

#include <limits>
#include <vector>
using GraphMat = std::vector<std::vector<int> >;
struct Vertex{
    bool known = false;
    int dist = std::numeric_limits<int>::max();
    int prev_id = -1;
};

class NodeHeap{
    /*node of heap*/
    public:
        int dist;
        int id;
        NodeHeap(int d, int i):dist(d), id(i){}
        NodeHeap(const NodeHeap& brother) {
            this->id = brother.id;
            this->dist= brother.dist;
        }
        NodeHeap():dist(-1), id(-1){ }
        bool operator >(const NodeHeap & rhs) const {
            return dist > rhs.dist;
        }
        bool operator < (const NodeHeap & rhs) const {
            return dist < rhs.dist;
        }
};

std::vector<Vertex> prim_heap(GraphMat & graph);
#endif //MIN_SP_TREE_H
