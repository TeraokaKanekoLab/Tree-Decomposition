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

    void clique(vector<int>& nbrs)
    {
        for (int nbr1 : nbrs) {
            for (int nbr2 : nbrs) {
                if (nbr1 == nbr2)
                    continue;
                if (neighbors_of[nbr1].find(nbr2) == neighbors_of[nbr1].end())
                    neighbors_of[nbr1].insert(nbr2);
            }
        }
    }
};