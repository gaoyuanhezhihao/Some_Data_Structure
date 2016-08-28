#ifndef SHORTEST_PATH_HPP  
#define SHORTEST_PATH_HPP  

#include <vector>
#include <limits>
#include <string>
#include "BinaryHeap.h"
using GraphMat = std::vector<std::vector<int> >;

struct Vertex{
    bool known = false;
    int dist = std::numeric_limits<int>::max();
    int prev_id = -1;
};
class HeapVt{
    /*Heap vertex used for heap of vertex unknown.*/
    public:
        int dist;
        int id;
        HeapVt(int d, int i):dist(d), id(i){ }
        HeapVt(const HeapVt& brother) {
            this->id = brother.id;
            this->dist = brother.dist;
        }
        HeapVt():dist(-1), id(-1){}
        bool operator >(const HeapVt & rhs) const {
            return dist > rhs.dist;
        }
        bool operator <(const HeapVt & rhs) const {
            return dist < rhs.dist;
        }

};
std::ostream & operator << (std::ostream & output, const HeapVt &data );
std::vector<Vertex> unweighted(GraphMat &graph, int id_start);
std::vector<Vertex> Dijkstra(GraphMat & graph, int id_start);
std::vector<Vertex> Dijkstra_heap(GraphMat &graph, int id_start);
bool print_all_pathes(std::vector<Vertex> & vt_path, std::vector<std::string> name_vtxes);
int find_min_dist_id(const std::vector<Vertex> & vt_path);
int find_min_dist_id(BinaryHeap<HeapVt> & heap_vt, const vector<Vertex> & vt_path);
#endif //SHORTEST_PATH_HPP  
