/*
min-deg-heu.cpp

Created by Cirus Thenter on 2020/08/27.
Copyright © 2020 Cirus Thenter. All rights reserved?

# how to run this program
% g++ min-deg-heu.cpp -o min-deg-heu
% ./min-deg-heu <graph data file>


# gaph data format
<# of nodes> <# of edges>
<endpoint 1> <endpoint 2>
<endpoint 3> <endpoint 4>
.
.
.

<endpoint n> needs to be int (edge No.)
*/

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MAX_TREE_WIDTH 100

using namespace std;

struct graph {
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int num_edges = 0;
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;
    string filename;
    string path;

    void add_edge(int u, int v)
    {
        edges.push_back({ u, v });
    }

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
        }
    }

    void read_edges(string file_name)
    {
        ifstream graph_data(file_name);
        int idx = file_name.find("graph/");
        filename = file_name.substr(idx + 6);
        path = file_name.substr(0, idx);

        if (!graph_data.good()) {
            cout << filename << ": file not found" << endl;
            exit(-1);
        }

        // ignore commented out lines
        string tp;
        streampos oldpos = graph_data.tellg();
        while (getline(graph_data, tp)) {
            if (tp.find("#") == string::npos) {
                graph_data.seekg(oldpos);
                break;
            }
            oldpos = graph_data.tellg();
        }

        // start reading edge information from file
        int u, v;
        while (graph_data >> u >> v) {
            add_edge(u, v);
            // compute number of nodes (|V|) and number of edges (|E|)
            num_nodes = max(num_nodes, max(u, v) + 1);
            num_edges++;
        }
        graph_data.close();
    }

    vector<int> parent;
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

    void decompose(int max_tree_width)
    {
        typedef pair<int, int> node; // (deg, vertex)
        int tree_width = 0;
        parent.resize(num_nodes);
        priority_queue<node, vector<node>, greater<node>> Q;
        int true_num_nodes = num_nodes;
        int remove_cnt = 0;
        ofstream output(path + "output/" + to_string(max_tree_width) + "-" + filename);
        vector<bool> retrieved;

        for (int u = 0; u < num_nodes; ++u) {
            parent[u] = u;
            Q.push(node(adj[u].size(), u));
            retrieved.push_back(false);
        }

        // start with the first node of the first edge.
        int nd = edges[0].first;
        retrieved[nd] = true;
        Q.push(node(adj[nd].size(), nd));
        for (int nb : adj[nd]) {
            retrieved[nb] = true;
            Q.push(node(adj[nb].size(), nb));
        }

        while (!Q.empty()) {
            int deg = Q.top().first;
            int u = Q.top().second;
            Q.pop();

            vector<int> nbh = neighbor(u); // get all the neighbours
            int true_deg = (int)nbh.size();

            if (true_deg > deg) { // if true degree is larger than the degree
                Q.push({ true_deg, u });
                continue;
            }
            // print_neighbor(u, nbh);
            update_width(true_deg, tree_width, true_num_nodes, remove_cnt, output);
            contract(u);
        }
        export_info(tree_width, remove_cnt, true_num_nodes, output);
        output.close();
    }

    void update_width(int& true_deg, int& tree_width, int& true_num_nodes, int& remove_cnt, ofstream& output)
    {
        if (true_deg > tree_width) {
            if (tree_width == 0) {
                true_num_nodes = num_nodes - remove_cnt;
                cout << "true num_nodes: " << true_num_nodes << endl;
                output << true_num_nodes << endl;
                remove_cnt = 0; // reset the count; we don't need nodes that have 0 edge
            } else
                export_info(tree_width, remove_cnt, true_num_nodes, output);
            tree_width = true_deg;
        }
        remove_cnt++;
    }

    void export_info(int tree_width, int remove_cnt, int true_num_nodes, ofstream& output)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)" << endl;
        output << tree_width << " " << remove_cnt << endl;
    }

    void print_info()
    {
        cout << "nodes: " << num_nodes << ", edges: " << num_edges << endl;
        return;
    }

    void print_neighbor(int u, vector<int> nbh)
    {
        cout << u << ": [";
        for (int i = 0; i < nbh.size(); ++i) {
            if (i == nbh.size() - 1)
                cout << nbh[i];
            else
                cout << nbh[i] << ", ";
        }
        cout << "]" << endl;
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }

    graph g;
    g.read_edges(argv[1]);
    g.make_graph();

    auto start = chrono::high_resolution_clock::now();
    g.decompose(stoi(argv[2]));
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    cout << double(duration.count()) / 1000000 << " s" << endl;

    return 0;
}
