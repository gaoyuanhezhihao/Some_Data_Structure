#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "graphviz_plot.h"
#include "shortest_path.h"

#define DIJKSTRA_HEAP
using namespace std;
using GraphMat = std::vector<vector<int> >;
bool read_graph(char * file_name, vector<vector<int> > & graph, vector<string> & name_vtxes);
void print_graph_mat(GraphMat & graph);

int main(int argc, char ** argv) {
    if(argc < 2) {
        std::cout << "Error: At Least Two Arguments." << endl;
        exit(-1);
    }
    std::vector<vector<int> > graph;
    std::vector<string> name_vtxes;
    read_graph(argv[1], graph, name_vtxes);
#ifdef DIJKSTRA
    cout << "=== Dijkstra=== " << endl;
    std::vector<Vertex> vt_pathes;
    vt_pathes = Dijkstra(graph, 0);
    print_all_pathes(vt_pathes, name_vtxes);
#endif //DIJKSTRA
#ifdef DIJKSTRA_HEAP
    cout << "=== Dijkstra_heap === " << endl;
    print_graph_mat(graph);
    std::vector<Vertex> vt_pathes;
    vt_pathes = Dijkstra_heap(graph, 0);
    print_all_pathes(vt_pathes, name_vtxes);
#endif //DIJKSTRA_HEAP 
    //print_graph_mat(graph);
    //unweighted(graph, 2);
    //plot_graph(graph,"t.dot", "ninja", name_vtxes);
}
void print_graph_mat(GraphMat & graph) {
    auto it=graph.cbegin(), graph_end=graph.cend();
    while(it != graph_end) {
        auto it_vertex=it->cbegin(), end_vertex=it->cend();
        while(it_vertex != end_vertex) {
            std::cout << *it_vertex << " "; 
            ++ it_vertex;
        }
        std::cout<< std::endl;
        ++ it;
    }
}

bool read_graph(char * file_name, vector<vector<int> > & graph, vector<string> & name_vtxes) {
    std::ifstream inFile(file_name);
    std::string line;
    //-- #1 first line is used for vertex name
    if(inFile.is_open()) {
        std::getline(inFile, line);
        std::istringstream iss(line);
        std::copy(istream_iterator<string>(iss), istream_iterator<string> (), std::back_inserter(name_vtxes));
    }else {
        std::cerr<< "failed to open file." << std::endl;
    }

    //-- #2 read graph data.
    while(std::getline(inFile, line)) {
        if(line[0] == '/' && line[1] == '/') {
            continue;
        }
        std::istringstream iss(line);
        vector<int> vertex{std::istream_iterator<int>{iss}, std::istream_iterator<int>{}};
        graph.push_back(std::move(vertex));
        //std::cout << line << std::endl;
    }
    return true;
}
