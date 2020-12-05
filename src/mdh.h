#include "graph.h"

class mdh : public Graph {
public:
    unordered_map<int, unordered_set<int>> neighbors_of;

    void make_graph()
    {
        for (pair<int, int> e : edges) {
            neighbors_of[e.first].insert(e.second);
            neighbors_of[e.second].insert(e.first);
        }
    }
};