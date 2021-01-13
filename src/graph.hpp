#include "eccentricity.hpp"
#include "header.hpp"

class Graph {
    typedef pair<int, int> edge;
    unordered_map<int, unordered_set<int>> neighbors_of;
    int array_size;
    int num_edges;

public:
    void add_edge(int u, int v)
    {
        if (u > v)
            swap(u, v);
        if (u == v)
            return;
        neighbors_of[u].insert(v);
        neighbors_of[v].insert(u);
        if (u + 1 > array_size)
            array_size = u + 1;
        if (v + 1 > array_size)
            array_size = v + 1;
    }

    int get_num_edges()
    {
        return num_edges;
    }

    int get_num_nodes()
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

    double compute_average_degree()
    {
        int sum = 0;
        for (auto node : neighbors_of) {
            sum += node.second.size();
        }

        return (double)sum / get_num_nodes();
    }

    int find_max_degree()
    {
        int max_d = 0;
        for (auto node : neighbors_of) {
            int d = node.second.size();
            if (d > max_d)
                max_d = d;
        }

        return max_d;
    }

    void read_graph(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << path << ": graph file not found" << endl;
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

        for (auto node : neighbors_of) {
            num_edges += node.second.size();
        }
        num_edges /= 2;
    }

    vector<int> compute_centers(vector<pair<int, int>> ecs)
    {
        vector<int> min_eccs;
        int min = ecs[0].second;
        for (pair<int, int> ec : ecs)
            if (ec.second < min)
                min = ec.second;
        for (pair<int, int> ec : ecs)
            if (ec.second == min)
                min_eccs.push_back(ec.first);
        return min_eccs;
    }

    vector<double> average_dist_from_vectors(vector<int> centers)
    {
        vector<double> sum_dists(array_size, 0);
        for (int center : centers) {
            vector<int> dists = shortest_dists_from(center);
            for (int i = 0; i < array_size; ++i)
                sum_dists[i] += dists[i];
        }
        for (int i = 0; i < array_size; ++i)
            sum_dists[i] /= centers.size();
        return sum_dists;
    }

    vector<int> shortest_dists_from(int s)
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
            for (auto nb : neighbors_of[nd])
                if (dist + COST < d[nb]) {
                    d[nb] = dist + COST;
                    pq.push(node(d[nb], nb));
                }
        }
        for (int i = 0; i < array_size; ++i)
            if (d[s] == INF)
                d[s] = 0;
        return d;
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

    vector<int> neighbors(int nd)
    {
        vector<int> neighbors;
        for (auto nb : neighbors_of[nd])
            neighbors.push_back(nb);
        return neighbors;
    }

    double compute_clustering_coefficient(int nd)
    {
        vector<int> nbs = neighbors(nd);
        int d = nbs.size(); // degree of nd
        if (d < 2)
            return 0;
        int cnt = 0; // # of edges in any pairs of neighbors
        for (int nb1 : nbs)
            for (int nb2 : nbs)
                if (neighbors_of[nb1].find(nb2) != neighbors_of[nb1].end())
                    cnt++;
        return (double)cnt / (d * (d - 1));
    }

    double compute_average_clustering()
    {
        double sum_clus = 0;
        for (auto node : neighbors_of) {
            int nd = node.first;
            sum_clus += compute_clustering_coefficient(nd);
        }
        return sum_clus / get_num_nodes();
    }

    vector<int> k_core()
    {
        typedef pair<int, int> node;
        vector<int> degrees(array_size, -1);
        priority_queue<node, vector<node>, greater<node>> degreeq;
        vector<int> k_core(array_size, -1);
        for (auto nd : neighbors_of) {
            int v = nd.first;
            int d = nd.second.size();
            degrees[v] = d;
            degreeq.push(node(d, v));
        }

        int k = 1;

        while (!degreeq.empty()) {
            pair<int, int> nd = degreeq.top();
            degreeq.pop();
            int v = nd.second;
            int d = nd.first;
            if (d != degrees[v])
                continue; // outdated entry
            while (k < d)
                k++;
            k_core[v] = k;
            degrees[v] = -1;
            for (int nb : neighbors_of[v]) {
                if (degrees[nb] < 0)
                    continue;
                degrees[nb]--;
                degreeq.push(node(degrees[nb], nb));
            }
        }

        return k_core;
    }

    double average_k_core()
    {
        vector<int> k_core_vector = k_core();
        int sum = 0;
        for (int k_core_size : k_core_vector)
            if (k_core_size > 0)
                sum += k_core_size;

        return (double)sum / get_num_nodes();
    }
};