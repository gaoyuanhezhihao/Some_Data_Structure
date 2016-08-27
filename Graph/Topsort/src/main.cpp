#include <iostream> 
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "graphviz_plot.hpp"
#include "TopSort.hpp"
using namespace std;
int main(int argc, char ** argv) {
    std::ifstream inFile(argv[1]);
    std::string line;
    std::vector<vector<int> > graph;
    if(argc < 2) {
        std::cout << "Error: At Least Two Arguments." << endl;
        exit(-1);
    }
    if(inFile.is_open()) {
        while(std::getline(inFile, line)) {
            std::istringstream iss(line);
            vector<int> vertex{std::istream_iterator<int>{iss}, std::istream_iterator<int>{}};
            graph.push_back(std::move(vertex));
            //std::cout << line << std::endl;
        }
    } else {
        std::cerr<< "failed to open file." << std::endl;
    }

    top_sort(graph);
    //auto it=graph.cbegin(), graph_end=graph.cend();
    //while(it != graph_end) {
        //auto it_vertex=it->cbegin(), end_vertex=it->cend();
        //while(it_vertex != end_vertex) {
            //std::cout << *it_vertex << " "; 
            //++ it_vertex;
        //}
        //std::cout<< std::endl;
        //++ it;
    //}
    //plot_graph(graph,"t.dot", "ninja");
}
