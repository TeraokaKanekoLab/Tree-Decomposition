#include "header.h"

string filename;
string type;

class Graph {
public:
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int true_num_nodes = 0;
    int remove_cnt = 0;
    vector<pair<int, int>> edges;
    stack<pair<int, vector<int>>> node_stack;
    typedef pair<int, int> node; // (deg, vertex)
    int max_tree_width = 0;

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

    void print_stack()
    {
        string output_name = "tree/" + type + "-" + to_string(max_tree_width) + "-" + filename + ".tree";
        ofstream output(output_name);
        vector<int> depth(num_nodes, 0);
        if (remove_cnt == true_num_nodes) {
            // print root node in the tree
            int root = node_stack.top().first;
            vector<int> root_nbrs = node_stack.top().second;
            node_stack.pop();
            output << root << endl;
            sort(root_nbrs.begin(), root_nbrs.end());
            for (int nbr : root_nbrs)
                output << nbr << " ";
            output << endl;
            output << "root" << endl;
        } else {
            output << "core" << endl;
            output << endl;
            output << endl;
        }

        while (!node_stack.empty()) {
            int nd = node_stack.top().first;
            vector<int> nbrs = node_stack.top().second;
            node_stack.pop();

            // ouput <nd> <nbr 1> <nbr 2> ... <nbr n> <parent>
            output << nd << endl;
            int parent = 0;
            int max_depth = -1;
            sort(nbrs.begin(), nbrs.end());
            for (int nbr : nbrs) {
                output << nbr << " ";
                if (depth[nbr] > max_depth) {
                    max_depth = depth[nbr];
                    parent = nbr;
                }
            }
            depth[nd] = max_depth + 1;
            output << endl;
            output << parent << endl;
        }
    }

    void add_to_stack(int nd, vector<int> nbrs)
    {
        vector<int> new_nbrs;
        for (int nbr : nbrs)
            if (nbr != nd)
                new_nbrs.push_back(nbr);
        node_stack.push(make_pair(nd, new_nbrs));
    }
};