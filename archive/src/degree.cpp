#include <algorithm>
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
            // add_edge(u, v);
            // compute number of nodes (|V|) and number of edges (|E|)
            // num_nodes = max(num_nodes, max(u, v) + 1);
            num_edges++;
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

    void count_edge()
    {
        typedef pair<int, int> node; // (deg, vertex)
        vector<node> nodes;
        int max_deg = 0;
        ofstream output(path + "degree/" + filename);

        for (int u = 0; u < num_nodes; ++u) {
            int deg = adj[u].size();
            max_deg = max(max_deg, deg);
            nodes.push_back(node(deg, u));
        }

        vector<int> deg_counts;
        for (int i = 0; i <= max_deg; ++i) {
            deg_counts.push_back(0);
        }

        for (node n : nodes) {
            int deg = n.first;
            deg_counts[deg]++;
        }
        output << num_edges << endl;
        for (int i = 1; i <= max_deg; ++i) {
            if (deg_counts[i] != 0)
                output << i << " " << deg_counts[i] << endl;
        }
    }
};

int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <filename>" << endl;
        exit(-1);
    }

    graph g;
    g.read_edges(argv[1]);
    g.make_graph();
    g.count_edge();

    return 0;
}
