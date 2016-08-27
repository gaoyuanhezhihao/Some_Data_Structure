#include "TopSort.hpp"
#include <vector>
#include <iostream>
using namespace std;
bool calc_vertex_info(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib, std::vector<int> & vertex_ref_count);
bool find_new_vertex(std::vector<int> & vertex_ref_count, deque<int> & next_vertexes);

bool top_sort(std::vector<std::vector<int> > &graph) {
    if(graph.size() == 0) {
        cout << "!Error: graph size if zero" << endl;
    }
    std::deque<int> next_vertexes;
    std::vector<std::vector<int> > vertex_neib(graph.size(), vector<int> ());
    std::vector<int> vertex_ref_count(graph.size(), 0);

    // #1 get information of graph.
    calc_vertex_info(graph, vertex_neib, vertex_ref_count);
    // #2 find first.
    find_new_vertex(vertex_ref_count, next_vertexes);
    size_t vertex_count = 0;
    while(false == next_vertexes.empty()) {
        int new_v = next_vertexes[0];
        ++ vertex_count;
        next_vertexes.pop_front();
        /* decrease ref count of neibor, and check if any of them is zero*/
        vector<int> & neib_id = vertex_neib[new_v];
        size_t j = 0;
        int tmp_id = 0;
        for(j= 0; j< neib_id.size();++j) {
            tmp_id = neib_id[j];
            if(vertex_ref_count[tmp_id] > 0) {
                vertex_ref_count[tmp_id] --;
            }
            if(vertex_ref_count[tmp_id] == 0) {
                next_vertexes.push_back(tmp_id);
                vertex_ref_count[tmp_id] = -1;
                cout << "* " << tmp_id << " ";
            }
        }
        cout << " | ";
    }
    if(vertex_count != graph.size()) {
        cout << "!WARNING: there is circle in this graph" << endl;
    }
    return true;
}

bool calc_vertex_info(std::vector<std::vector<int> > &graph, std::vector<std::vector<int> > & vertex_neib, std::vector<int> & vertex_ref_count) {
    if(graph.size() == 0 || graph[0].size() == 0 || graph.size() != graph[0].size()) {
        std::cout << "!Error: graph format is wrong..." << std::endl;
        exit(-1);
    }
    size_t r= 0, c=0;
    for(r=0;r<graph.size();++r) {
        for(c=0;c<graph[0].size();++c) {
            if(graph[r][c] > 0 ) { //r-->c
                vertex_ref_count[c] ++;
                vertex_neib[r].push_back(c);
            }
        }
    }
    return true;
}

bool find_new_vertex(std::vector<int> & vertex_ref_count, deque<int> & next_vertexes) {
    size_t i =0;
    bool found_any = false;
    for(i=0; i< vertex_ref_count.size(); ++i ) {
        if(vertex_ref_count[i] == 0) {
            next_vertexes.push_back(i);
            vertex_ref_count[i] = -1; // record this vertex has been enqueued.
            cout << "*"<< i<<" ";
            found_any = true;
        }
    }
    cout << " | " ;
    return found_any;
}
