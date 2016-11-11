#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H
#include <vector>

class DisjointSet {
    public:
        //--- function ---
        bool SetUnion(int id1, int id2);
        int find(int dst_id); // return root id.
        DisjointSet(int size):set_roots(size, -1){ }
        bool is_same_set(int l_id, int r_id);
        bool plot(const char name_plot[]);
        bool print();
        //=== function ===
        
        //--- data ---
        std::vector<int> set_roots;
        //=== data ===
};

#endif //DISJOINT_SET_H
