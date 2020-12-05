#include "graph.h"

struct sbr : public Graph {
public:
    vector<vector<int>> adj;
    vector<int> parent;
    typedef pair<int, int> node; // (deg, vertex)

    void make_graph()
    {
        adj.resize(num_nodes);
        for (pair<int, int> e : edges) {
            adj[e.first].push_back(e.second);
            adj[e.second].push_back(e.first);
        }
        for (vector<int> nbh : adj) {
            sort(nbh.begin(), nbh.end()); // sort endpoint indices in case edges are not sorted in the file as we expect
            nbh.erase(unique(nbh.begin(), nbh.end()), nbh.end()); // classic way of erasing duplicates;
            if (nbh.size())
                true_num_nodes++;
        }
        cout << true_num_nodes << endl;

        parent.resize(num_nodes);
        for (int u = 0; u < num_nodes; ++u) {
            parent[u] = u;
        }
    }

    int root(int v)
    { // union-find data structure
        if (parent[v] == v || parent[v] == -1)
            return v;
        return parent[v] = root(parent[v]);
    }

    void normalize(vector<int>& S)
    {
        for (auto& v : S)
            v = root(v);
        sort(S.begin(), S.end());
        S.erase(unique(S.begin(), S.end()), S.end());
    }

    vector<int> neighbor(int u)
    {
        vector<int> nbh;
        normalize(adj[u]);
        for (auto v : adj[u]) {
            if (parent[v] == v) {
                nbh.push_back(v);
            } else {
                normalize(adj[v]);
                for (auto w : adj[v]) {
                    if (parent[w] == w) {
                        nbh.push_back(w);
                    }
                }
            }
        }
        normalize(nbh);
        return nbh;
    }

    void contract(int u)
    {
        vector<int> live, dead;
        for (auto v : adj[u]) {
            if (parent[v] == v)
                live.push_back(v);
            else
                dead.push_back(v);
        }
        parent[u] = -1;
        adj[u].swap(live);
        for (auto v : dead) {
            normalize(adj[v]);
            adj[u].insert(adj[u].end(), adj[v].begin(), adj[v].end());
            adj[v].clear();
            parent[v] = u;
        }
    }
};