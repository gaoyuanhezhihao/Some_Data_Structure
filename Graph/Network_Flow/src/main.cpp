#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "graphviz_plot.h"
#include "network_flow.h"

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
    GraphMat flow_graph, residual_graph;
    std::vector<string> name_vtxes;
    read_graph(argv[1], graph, name_vtxes);
    net_flow(graph, flow_graph, residual_graph, 0, 5);
    cout << "graph:" << endl;
    print_graph_mat(graph);
    cout << "flow graph" << endl;
    print_graph_mat(flow_graph) ;
    cout << "residual graph" << endl;
    print_graph_mat(residual_graph) ;

    plot_graph_flow(graph, "tunnels", name_vtxes);
    plot_graph_flow(flow_graph,  "flow", name_vtxes);
    plot_graph_flow(residual_graph,  "residual", name_vtxes);
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
