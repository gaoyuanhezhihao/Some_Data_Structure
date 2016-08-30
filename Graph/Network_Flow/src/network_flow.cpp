#include "network_flow.h"
#include <vector>
#include <iostream>
#include "BinaryHeap.h"
using namespace std;
using GraphMat = std::vector<std::vector<int> >;
//---inline function---
vector<Vertex> dijk_max_path(const GraphMat& r_graph, int s_id, int t_id);
bool calc_vertex_info(const std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib);
int find_min_dist_id(BinaryHeap<NodeHeap> & heap_vt, const vector<Vertex> & vt_path);
void update_graph(GraphMat & flow_graph, GraphMat & r_graph, const vector<Vertex> &pathes, int t_id);
//===inline function===



int net_flow(const GraphMat & graph, GraphMat & flow_graph, GraphMat & residual_graph, int source_id, int sink_id) {
    //-- #0 init.
    residual_graph = graph;
    flow_graph = GraphMat(graph.size(), vector<int>(graph[0].size(), 0));
    vector<Vertex> pathes;
    int max_flow = 0;
    //-- #1 find path from source to sink pass max flow.
    while(true) {
        pathes = dijk_max_path(residual_graph, source_id, sink_id);
        if(0 == pathes.size()) {
            /*completed.*/
            return max_flow; 
        }
        //-- #2 update graphs.
        update_graph(flow_graph, residual_graph, pathes, sink_id);
    }


}



std::ostream & operator << (std::ostream & output, const NodeHeap &data) {
    output << '(' << data.dist << ',' << data.id << ')' ;
    return output;
}
void update_graph(GraphMat & flow_graph, GraphMat & r_graph, const vector<Vertex> &pathes,
        int t_id) {
    int id_now = t_id;
    const int flow = pathes[t_id].flow;
    int id_prev = pathes[id_now].prev_id;
    while(-1 != id_prev) {
        //-- #1.1 update flow graph.
        if(flow_graph[id_now][id_prev] > 0 ) {
            if(flow_graph[id_now][id_prev] < flow) {
                flow_graph[id_prev][id_now] = flow - flow_graph[id_now][id_prev];
                flow_graph[id_now][id_prev] = 0;
            }else{
                flow_graph[id_now][id_prev] -= flow;
            }
        } else {
            flow_graph[id_prev][id_now] += flow;
        }
        //-- #1.2 update residual graph.
        r_graph[id_prev][id_now] -= flow;
        r_graph[id_now][id_prev] += flow;
        //-- #2 move up.
        id_now = id_prev;
        id_prev = pathes[id_now].prev_id;
    }
}

vector<Vertex> dijk_max_path(const GraphMat& r_graph, int s_id, int t_id) {
    vector<Vertex> pathes(r_graph.size());
    pathes[s_id].flow = numeric_limits<int>::max();
    pathes[s_id].prev_id= -1;
    pathes[s_id].known = false;
    vector<vector<int> > vert_neib(r_graph.size(), vector<int> ());
    calc_vertex_info(r_graph, vert_neib);
    /*build heap*/
    vector<NodeHeap> tmp_data = {NodeHeap(-pathes[s_id].flow, s_id)};
    BinaryHeap<NodeHeap> heap_vt(tmp_data);
    //-- #1 interate until sink vertex.
    for(size_t i = 0;i< r_graph.size(); ++i) {
        int id_now = find_min_dist_id(heap_vt, pathes);
        if(-1 == id_now) {
            cout << "no more path from source to sink.."<< endl;
            return vector<Vertex>();
        }
        pathes[id_now].known = true;
        if(id_now == t_id) {
            /* arrived the sink vertex.*/
            return pathes;
        }
        int flow_now = pathes[id_now].flow;
        for(auto & n:vert_neib[id_now]) {
            int neib_flow = r_graph[id_now][n];
            int flow_expect = flow_now < neib_flow ?flow_now : neib_flow;
            if(false == pathes[n].known) {
                if(pathes[n].flow < flow_expect) {
                    pathes[n].prev_id = id_now;
                    pathes[n].flow = flow_expect;
                    heap_vt.insert(NodeHeap(- flow_expect, n));
                }
            }
        }
    }

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

bool calc_vertex_info(const std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib) {
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



