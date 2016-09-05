#ifndef MIN_SP_TREE_H
#define MIN_SP_TREE_H

#include <limits>
#include <vector>
#include <iostream>
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
class Edge{
    public:
        int len;
        int v;
        int w;
        Edge(int node_id1, int node_id2, int len):v(node_id1), w(node_id2), len(len){}
        Edge(const Edge& twins) {
           this->len = twins.len;
           this->v = twins.v;
           this->w = twins.w;
        }
        Edge():len(-1), v(-1), w(-1) {}
        bool operator > (const Edge & rhs) const{
            return len > rhs.len;
        }
        bool operator < (const Edge & rhs) const{
            return len < rhs.len;
        }
};
std::vector<Vertex> prim_heap(GraphMat & graph);
std::vector<std::vector<int> > kruskal(GraphMat & graph);
std::ostream & operator << (std::ostream & output, const Edge & ed);
#endif //MIN_SP_TREE_H
