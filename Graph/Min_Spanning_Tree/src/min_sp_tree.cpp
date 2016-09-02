#include <vector>
#include <iostream>
#include "min_sp_tree.h"
#include "BinaryHeap.h"

using namespace std;
using GraphMat = std::vector<vector<int> >;
//--- inline function ---
bool calc_vertex_info(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib);
int find_min_dist_id(BinaryHeap<NodeHeap> & heap_vt, const vector<Vertex> & vt_path);
bool check_graph(GraphMat & graph);
//=== inline function ===
vector<Vertex> prim_heap(GraphMat & graph)  {
    //-- #1 init.
    check_graph(graph);
    vector<Vertex> sp_tree(graph.size(), Vertex());
    sp_tree[0].dist = 0;
    sp_tree[0].known = false;
    sp_tree[0].prev_id = -1;
    vector<vector<int> > neibors(graph.size(), vector<int> ());
    calc_vertex_info(graph, neibors);
    /*build heap*/
    vector<NodeHeap> tmp_data={NodeHeap(0, 0)};
    BinaryHeap<NodeHeap> heap_vt(tmp_data);
    //-- #2 interate every vertex.
    for(size_t i = 0; i < graph.size(); ++i) {
        //-- #2.1 get next vertex.
        int id_now = find_min_dist_id(heap_vt, sp_tree);
        if(-1 == id_now) {
            cout << "!Error: there is isolated part in this graph." << endl;
            return vector<Vertex> ();
        }
        //-- #2.2 spread to neibors.
        for(auto &n: neibors[id_now]) {
            if(false == sp_tree[n].known) {
                int neib_dist = graph[id_now][n];
                if(sp_tree[n].dist > neib_dist) {
                    sp_tree[n].dist = neib_dist;
                    sp_tree[n].prev_id = id_now;
                    heap_vt.insert(NodeHeap(sp_tree[n].dist, n));
                }
            }
        }
        //-- #2.3 record id_now as known.
        sp_tree[id_now].known =true;
    }
    return sp_tree;
}
bool check_graph(GraphMat & graph) {
    /*check if the format of the graph is right.*/
    const int count = graph.size();
    int r = 0;
    int c = 0;
    for(r = 0; r< count ; ++r ) {
        if(graph[r][r] != 0){
            cout << "!Error: graph[r][r] != 0" << endl;
            return false;
        }
        for(c = r; c <count ; ++c) {
            if(graph[r][c] != graph[c][r]) {
                cout << "!Error: graph[r][c] != graph[c][r]" << endl;
                return false;
            }
        }
    }
    return true;
}
int find_min_dist_id(BinaryHeap<NodeHeap> & heap_vt, const vector<Vertex> & vt_path) {
    NodeHeap tmp_vt(-1, -1);
    do{
        if(heap_vt.isEmpty()) {
            return -1;
        }
        heap_vt.deleteMin(tmp_vt);
    }while(true == vt_path[tmp_vt.id].known);
    return tmp_vt.id;
}

bool calc_vertex_info(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib) {
    if(graph.size() == 0 || graph[0].size() == 0 || graph.size() != graph[0].size()) {
        std::cout << "!Error: graph format is wrong..." << std::endl;
        exit(-1);
    }
    size_t r= 0, c=0;
    for(r=0;r<graph.size();++r) {
        for(c=0;c<graph[0].size();++c) {
            if(graph[r][c] > 0 ) { //r-->c
                vertex_neib[r].push_back(c);
            }
        }
    }
    return true;
}


