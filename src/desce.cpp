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
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#define MAX_TREE_WIDTH 100

using namespace std;

typedef pair<int, int> node; // (deg, vertex)

string file_name;
string filename;
string path;

struct graph {
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int true_num_nodes = 0;
    int num_edges = 0;
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;
    vector<int> parent;
    vector<node> nodes;

    void add_edge(int u, int v)
    {
        edges.push_back({ u, v });
    }

    void read_edges()
    {
        ifstream graph_data(file_name);

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

        parent.resize(num_nodes);
        for (int u = 0; u < num_nodes; ++u) {
            parent[u] = u;
            nodes.push_back(node(adj[u].size(), u));
        }
        sort(nodes.begin(), nodes.end(), greater());
    }

    struct greater {
        template <class T>
        bool operator()(T const& a, T const& b) const { return a > b; }
    };

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

    void decompose(int max_tree_width, ofstream& output)
    {
        int tree_width = 0;
        int remove_cnt = 0;

        for (node nd : nodes) {
            int deg = nd.first;
            int u = nd.second;

            vector<int> nbh = neighbor(u); // get all the neighbours
            int true_deg = (int)nbh.size();

            if (true_deg > max_tree_width)
                continue;
            // print_neighbor(u, nbh);
            if (true_deg)
                remove_cnt++;
            contract(u);
        }
        export_info(max_tree_width, remove_cnt, output);
    }

    void export_info(int tree_width, int remove_cnt, ofstream& output)
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

void copy_master(graph& g, graph& master)
{
    g.num_nodes = master.num_nodes; // This value may be different from the official number of nodes.
    g.true_num_nodes = master.true_num_nodes;
    g.num_edges = master.num_edges;
    g.adj = master.adj;
    g.edges = master.edges;
    g.parent = master.parent;
    g.nodes = master.nodes;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }
    file_name = argv[1];
    int idx = file_name.find("graph/");
    filename = file_name.substr(idx + 6);
    path = file_name.substr(0, idx);
    int max_width = stoi(argv[2]);
    ofstream output(path + "output/" + to_string(max_width) + "-desce-" + filename);
    graph master;
    master.read_edges();
    master.make_graph();
    graph g;
    for (int width = 0; width < max_width;) {
        if (width < 10)
            width++;
        else
            width += width / 10;
        if (width >= max_width)
            width = max_width;
        copy_master(g, master);
        g.decompose(width, output);
    }
    output.close();

    return 0;
}
