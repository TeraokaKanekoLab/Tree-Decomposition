#include "header.hpp"

class Graph {
    typedef pair<int, int> edge;
    vector<bool> nodes;
    vector<edge> edges;
    unordered_map<int, unordered_set<int>> neighbors_of;

public:
    void add_edge(int u, int v)
    {
        if (u > v)
            swap(u, v);
        edges.push_back({ u, v });
        neighbors_of[u].insert(v);
        neighbors_of[v].insert(u);
    }

    int num_edges()
    {
        return edges.size();
    }

    int num_nodes()
    {
        return neighbors_of.size();
    }

    int array_size()
    {
        return nodes.size();
    }

    bool vector_is_small(int nd)
    {
        return nd > (int)nodes.size() - 1;
    }

    void add_node(int nd)
    {
        if (vector_is_small(nd))
            nodes.resize(nd + 1);
        nodes[nd] = true;
    }

    bool exists(int nd)
    {
        if (vector_is_small(nd))
            return false;
        return nodes[nd];
    }

    void read_edges(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << "graph file not found" << endl;
            exit(-1);
        }

        // ignore commented out lines
        string tp;
        streampos oldpos = file.tellg();
        while (getline(file, tp)) {
            if (tp.find("#") == string::npos) {
                file.seekg(oldpos);
                break;
            }
            oldpos = file.tellg();
        }

        int u, v;
        while (file >> u >> v) {
            add_edge(u, v);
            add_node(u);
            add_node(v);
        }
        file.close();
    }

    int shortest_dist(int s, int t)
    {
        int INF = INT_MAX;
        int COST = 1; // unweighted
        vector<int> d(array_size(), INF);
        d[s] = 0;
        typedef pair<int, int> node; // <dist, id>
        priority_queue<node, vector<node>, greater<node>> pq;
        pq.push(node(0, s));
        while (!pq.empty()) {
            node v = pq.top();
            pq.pop();
            int nd = v.second;
            int dist = v.first;
            if (nd == t)
                return dist;
            for (auto nb : neighbors_of[nd])
                if (dist + COST < d[nb]) {
                    d[nb] = dist + COST;
                    pq.push(node(d[nb], nb));
                }
        }
        return INF;
    }
};