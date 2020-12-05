#include "header.h"

string filename;

class Graph {
public:
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int true_num_nodes = 0;
    vector<pair<int, int>> edges;
    stack<pair<int, vector<int>>> node_stack;

public:
    void add_edge(int u, int v)
    {
        edges.push_back({ u, v });
    }

    void read_edges()
    {
        ifstream graph_data("graph/" + filename + ".gr");

        if (!graph_data.good()) {
            cout << "file not found" << endl;
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
        }
        graph_data.close();
    }
    void export_info(int tree_width, int remove_cnt, int true_num_nodes, ofstream& output, chrono::microseconds duration)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)"
             << " " << double(duration.count()) / 1000000 << endl;
        output << tree_width << " " << remove_cnt << " " << double(duration.count()) / 1000000 << endl;
    }
};