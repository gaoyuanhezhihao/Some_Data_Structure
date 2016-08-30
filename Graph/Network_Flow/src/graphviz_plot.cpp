#include "graphviz_plot.h"

PlotRet plot_graph(GraphDataType const & graph, const char file_name[], const string name_graph, vector<string> & name_vtxes) {
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return PlotRet::fail_to_open_file;
    }
    file_stream << "digraph " << name_graph << "{\n";
    int count = graph.size();
    int r=0;
    int c=0;
    //cout << count<< endl;
    for(r=0;r<count; ++ r) {
        //cout <<graph[r].size() << endl;
        for(c=0;c<count;++c) {
            
            if(graph[r][c] > 0){
                file_stream << name_vtxes[r] << "->" << name_vtxes[c]<< "\n";
            }
        }
    }
    file_stream << "}" << endl;
    string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+ name_graph + ".png");
    std::cout << cmd << endl;
    system(cmd.c_str());
    return PlotRet::success;
}

PlotRet plot_graph_flow(GraphDataType const & graph, const string name_graph, vector<string> & name_vtxes) {
    string file_name =name_graph + ".dot";
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return PlotRet::fail_to_open_file;
    }
    file_stream << "digraph " << name_graph << "{\n";
    int count = graph.size();
    int r= 0;
    int c= 0;
    ////-- #1 plot vertex label.
    //for(r = 0; r< count ; ++r ) {
       //cout << r << "[label=jj" 

    //}
    //-- #2 plot line label.
    for(r=0; r<count ;++r) {
        for(c=0; c<count; ++c) {
            if(graph[r][c] > 0) {
                file_stream << name_vtxes[r] << "->" << name_vtxes[c] << " [label=\""<<graph[r][c] << "\", fontcolor=darkgreen]\n";
            }
        }
    }
    file_stream << "}" << endl;
    string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+name_graph+".png");
    std::cout <<cmd << endl;
    system(cmd.c_str());
    return PlotRet::success;
}
//GraphPloter::GraphPloter(const char * name):name_str(name) {
    //file_stream.open(name_str+".dot", std::ofstream::out);
    //file_stream << "digraph " << name_graph << "{\n";
//}
//bool GraphPloter::add_line(int l, int r) {
    //file_stream << l << "->" << r << "\n";
    //return true;
//}
//GraphPloter::~GraphPloter() {
    //file_stream << "}" << endl;
    //string cmd{"dot -Tpng "};
    //cmd += (name_str+".dot ");
    //cmd += (" -o ./"+ name_str + ".png");
    //std::cout << cmd << endl;
    //system(cmd.c_str());
//}
