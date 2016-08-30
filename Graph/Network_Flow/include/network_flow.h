#ifndef NETWORK_FLOW_H
#define NETWORK_FLOW_H

#include <iostream>
#include <limits>
#include <vector>
using GraphMat = std::vector<std::vector<int> >;
//---data---
struct Vertex{
    bool known = false;
    int flow= std::numeric_limits<int>::min();
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

//---function---
std::ostream & operator << (std::ostream & output, const NodeHeap & data);

int net_flow(const GraphMat & graph, GraphMat & flow_graph, GraphMat & residual_graph, int source_id, int sink_id);
#endif //NETWORK_FLOW_H
