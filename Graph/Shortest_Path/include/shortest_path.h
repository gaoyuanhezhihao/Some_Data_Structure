#ifndef SHORTEST_PATH_HPP  
#define SHORTEST_PATH_HPP  

#include <vector>
#include <limits>
#include <string>
using GraphMat = std::vector<std::vector<int> >;

struct Vertex{
    bool known = false;
    int dist = std::numeric_limits<int>::max();
    int prev_id = -1;
};
std::vector<Vertex> unweighted(GraphMat &graph, int id_start);
std::vector<Vertex> Dijkstra(GraphMat & graph, int id_start);
bool print_all_pathes(std::vector<Vertex> & vt_path, std::vector<std::string> name_vtxes);
int find_min_dist_id(const std::vector<Vertex> & vt_path);
#endif //SHORTEST_PATH_HPP  
