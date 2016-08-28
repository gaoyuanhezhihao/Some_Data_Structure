#include "shortest_path.h"
#include <vector>
#include <deque>
#include <iostream>
#include <limits>
#include "BinaryHeap.h"
using namespace std;
using GraphMat = std::vector<vector<int> >;
// -------function declare-----------------------------
bool calc_vertex_info(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib);
//--------function definition-----------------------------------
vector<Vertex> unweighted(GraphMat &graph, int id_start) {
    //-- #1 init.
    vector<Vertex> vts(graph.size(), Vertex());
    vector<vector<int> > vert_neib(graph.size(), vector<int> ());
    calc_vertex_info(graph, vert_neib);
    //-- #2 init queue.
    std::deque<int> next_vxes; 
    next_vxes.push_back(id_start);
    vts[id_start].dist = 0;
    //-- #3 process every element of queue until end.
    while(false == next_vxes.empty()) {
        int id = next_vxes[0];
        cout << id<<'('<< vts[id].dist<<')' << "-->";
        next_vxes.pop_front();
        /*check neibor.*/
        for(auto &n:vert_neib[id]) {
            if(vts[n].dist == -1) {
                vts[n].dist = vts[id].dist +1;
                vts[n].prev_id = id;
                next_vxes.push_back(n);
            }
        }
    }
    return vts;
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

vector<Vertex> Dijkstra_heap(GraphMat &graph, int id_start) {
    //-- #1 init.
    vector<Vertex> vt_path(graph.size(), Vertex());
    vt_path[id_start].dist = 0;
    vt_path[id_start].known = false; 
    vt_path[id_start].prev_id = -1;
    vector<vector<int> > vert_neib(graph.size(), vector<int> ());
    calc_vertex_info(graph, vert_neib);
    size_t i = 0;
    /*build heap*/
    vector<HeapVt> tmp_data={HeapVt(0, id_start)};
    BinaryHeap<HeapVt> heap_vt(tmp_data) ;
    heap_vt.print();
    //-- #2  interate every vertex.
    for(i = 0; i< graph.size(); ++i) {
        int id_next = find_min_dist_id(heap_vt, vt_path);
        if(-1 == id_next) {
            cout << "!WARNING: There is isolated part." << endl;
            break;
        }
        vt_path[id_next].known = true;
        for(auto & n:vert_neib[id_next]) {
            int neib_dist = graph[id_next][n];
            if(false == vt_path[n].known){
                if(vt_path[n].dist > vt_path[id_next].dist + neib_dist){
                    vt_path[n].dist = vt_path[id_next].dist + neib_dist;
                    vt_path[n].prev_id = id_next;
                    heap_vt.insert(HeapVt(vt_path[n].dist, n));
                }
            }

        }
        heap_vt.print();
    }
    return vt_path;

}
vector<Vertex> Dijkstra(GraphMat & graph, int id_start) {
    vector<Vertex> vt_path(graph.size(), Vertex());
    vt_path[id_start].dist = 0;
    vt_path[id_start].known = false; 
    vt_path[id_start].prev_id = -1;
    vector<vector<int> > vert_neib(graph.size(), vector<int> ());
    calc_vertex_info(graph, vert_neib);
    int id_min_dist = 0;
    size_t i = 0;
    //-- #1 interate every vertex.
    for(i = 0; i< graph.size(); ++i) {
        /*find unknown vertex with min dist.*/
        id_min_dist = find_min_dist_id(vt_path);
        if(-1 == id_min_dist) {
            cout << "!WARNING: There is isolated part" << endl;
            break;
        }
        vt_path[id_min_dist].known = true;
        /*update neibor vertex.*/
        for(auto & n:vert_neib[id_min_dist]) {
            int neib_dist = graph[id_min_dist][n];
            if(false == vt_path[n].known && vt_path[n].dist > vt_path[id_min_dist].dist + neib_dist) {
                vt_path[n].dist = vt_path[id_min_dist].dist + neib_dist;
                vt_path[n].prev_id = id_min_dist;
            }
        }

    }
    return vt_path;
}
bool print_all_pathes(vector<Vertex> & vt_path, vector<string> name_vtxes) {
    size_t i = 0;
    size_t id_father = 0;
    for(i = 0; i< vt_path.size(); ++i) {
        /* print path to i-th vertex*/
        string path=name_vtxes[i]+'('+std::to_string(vt_path[i].dist)+')';
        id_father = vt_path[i].prev_id;
        while(id_father != -1){
            path = name_vtxes[id_father] + "-->" + path;
            id_father = vt_path[id_father].prev_id;
        }
        cout << path << endl;
    }
    return true;
}
int find_min_dist_id(const vector<Vertex> & vt_path) {
    int i = 0;
    int min_dist = std::numeric_limits<int>::max() ;
    int id_min = -1;
    for(i = 0; i< vt_path.size(); ++i) {
        if(false == vt_path[i].known && vt_path[i].dist < min_dist) {
            id_min = i;
            min_dist = vt_path[id_min].dist; 
        }
    }
    return id_min;
}
int find_min_dist_id(BinaryHeap<HeapVt> & heap_vt, const vector<Vertex> & vt_path) {
    HeapVt tmp_vt(-1, -1);
    do{
        if(heap_vt.isEmpty()) {
            return -1;
        }
        heap_vt.deleteMin(tmp_vt);
    }while(true == vt_path[tmp_vt.id].known);
    return tmp_vt.id;
}

std::ostream & operator << (std::ostream & output, const HeapVt &data ) {
    output << '(' << data.dist<< ',' << data.id<< ')'; 
    return output;
}
