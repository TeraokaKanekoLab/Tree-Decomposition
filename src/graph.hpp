#include "header.hpp"

class Graph {
    typedef pair<int, int> edge;
    vector<edge> edges;
    unordered_map<int, unordered_set<int>> neighbors_of;
    int array_size;

public:
    void add_edge(int u, int v)
    {
        if (u > v)
            swap(u, v);
        edges.push_back({ u, v });
        neighbors_of[u].insert(v);
        neighbors_of[v].insert(u);
        if (u + 1 > array_size)
            array_size = u + 1;
        if (v + 1 > array_size)
            array_size = v + 1;
    }

    int num_edges()
    {
        return edges.size();
    }

    int num_nodes()
    {
        return neighbors_of.size();
    }

    bool exists(int nd)
    {
        return neighbors_of.find(nd) != neighbors_of.end();
    }

    int degree(int nd)
    {
        if (!exists(nd)) {
            return -1;
        }
        return neighbors_of[nd].size();
    }

    void read_graph(string path)
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
        while (file >> u >> v)
            add_edge(u, v);
        file.close();
    }

    int shortest_dist(int s, int t)
    {
        int INF = INT_MAX;
        int COST = 1; // unweighted
        vector<int> d(array_size, INF);
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

    int compute_eccentricity(int s)
    {
        int eccentricity = 0;

        int INF = INT_MAX;
        int COST = 1; // unweighted
        vector<int> d(array_size, INF);
        d[s] = 0;
        typedef pair<int, int> node; // <dist, id>
        priority_queue<node, vector<node>, greater<node>> pq;
        pq.push(node(0, s));
        while (!pq.empty()) {
            node v = pq.top();
            pq.pop();
            int nd = v.second;
            int dist = v.first;
            for (auto nb : neighbors_of[nd])
                if (dist + COST < d[nb]) {
                    d[nb] = dist + COST;
                    pq.push(node(d[nb], nb));
                    if (d[nb] > eccentricity)
                        eccentricity = d[nb];
                }
        }

        return eccentricity;
    }
};