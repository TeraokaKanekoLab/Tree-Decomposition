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
#include <set>
#include <string>
#include <vector>

using namespace std;

struct graph {
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0;
    int num_edges = 0;
    vector<vector<int>> adj;
    vector<pair<int, int>> edges;

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
            nbh.erase(unique(nbh.begin(), nbh.end()), nbh.end());
        }
    }

    void read_edges(string filename)
    {
        ifstream graph_data(filename);

        if (!graph_data.good()) {
            cout << filename << ": file not found" << endl;
            exit(-1);
        }

        // Read edge information from file
        int u, v;
        while (graph_data >> u >> v) {
            add_edge(u, v);
            // compute number of nodes (|V|) and number of edges (|E|)
            num_nodes = max(num_nodes, max(u, v) + 1);
            num_edges++;
        }
        graph_data.close();
    }
};

void print_adj_matrix(int num_nodes, const vector<vector<bool>>& adj_matrix)
{
    cout << "  ";
    for (int i = 0; i < num_nodes; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < num_nodes; ++i) {
        cout << i << " ";
        for (int j = 0; j < num_nodes; ++j) {
            if (adj_matrix[i][j])
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>" << endl;
        exit(-1);
    }

    graph g;
    g.read_edges(argv[1]);

    return 0;
}