#ifndef GRAPHVIZ_PLOT_HPP
#define GRAPHVIZ_PLOT_HPP

#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> //system()
#include <iostream>
#include "min_sp_tree.h"

using namespace std;
using GraphDataType= std::vector< std::vector<int> >;
enum class PlotRet{
    success,
    fail_to_open_file,
};

PlotRet plot_graph(GraphDataType const & graph, const char file_name[], const string name_graph, vector<string> & name_vtxes);
PlotRet plot_sp_tree(std::vector<Vertex> & sp_tree, const string name_tree, vector<string> & name_vtxes);
PlotRet plot_undigraph(GraphDataType const & graph, const string name_graph, vector<string> &name_vtxes);
PlotRet plot_kruskal_sp_tree(const std::vector<std::vector<int> >& pathes, const string name_tree,  const std::vector<std::string> & name_vtxes);

class GraphPloter{
    private:
        std::string name_str;
        std::ofstream file_stream;
    public:
        GraphPloter(const char * name);
        bool add_line(int l, int r);
        ~GraphPloter();
};
#endif //GRAPHVIZ_PLOT_HPP

