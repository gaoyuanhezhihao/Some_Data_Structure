#include "graphviz_plot.h"
#include "min_sp_tree.h"

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
PlotRet plot_kruskal_sp_tree(const std::vector<std::vector<int> >& pathes, const string name_tree,  const std::vector<std::string> & name_vtxes) {
    const string file_name = name_tree + ".dot";
    ofstream file_stream(file_name);
    if(false == file_stream.is_open())  {
        return PlotRet::fail_to_open_file;
    }
    file_stream << "graph " << name_tree << "{\n" ;
    for(size_t i = 0; i < pathes.size(); ++ i) {
        for(auto n:pathes[i]) {
            file_stream << name_vtxes[i] << " -- " << name_vtxes[n] << ";\n";
        }
    }
    file_stream << "}" << endl;
    string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+ name_tree+ ".png");
    std::cout << cmd << endl;
    system(cmd.c_str());
    return PlotRet::success;
}

PlotRet plot_sp_tree(std::vector<Vertex> & sp_tree, const string name_tree, vector<string> & name_vtxes) {
    const string file_name = name_tree+ ".dot";
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return PlotRet::fail_to_open_file;
    }
    file_stream << "graph " << name_tree<< "{\n";
    for(size_t i = 0; i< sp_tree.size(); ++i) {
        if(sp_tree[i].prev_id >= 0 ) {
            file_stream << name_vtxes[sp_tree[i].prev_id] << " -- " << name_vtxes[i] << ";\n";
        }
    }
    file_stream << "}" << endl;
    string cmd{"dot -Tpng "};
    cmd += file_name;
    cmd += (" -o ./"+ name_tree+ ".png");
    std::cout << cmd << endl;
    system(cmd.c_str());
    return PlotRet::success;
}
PlotRet plot_undigraph(GraphDataType const & graph, const string name_graph, vector<string> &name_vtxes) {
    const string file_name = name_graph + ".dot";
    std::ofstream file_stream(file_name);
    if(false == file_stream.is_open()) {
        return PlotRet::fail_to_open_file;
    }
    file_stream << "graph " << name_graph << "{\n";
    int count = graph.size();
    int r = 0;
    int c= 0;
    for(r =0; r< count ; ++r) {
        for(c=r;c<count;++c) {
            if(graph[r][c] >0 ) {
                file_stream << name_vtxes[r] << " -- " << name_vtxes[c] << ";\n";
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
