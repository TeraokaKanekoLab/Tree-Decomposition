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
    deque<pair<int, vector<int>>> node_stack;
    typedef pair<int, int> node; // (deg, vertex)
    int max_tree_width = 0;
    vector<int> depth;
    vector<int> parents;
    int depth_of_tree = 0;
    int leaf_cnt = 0;
    int total_child_cnt = 0;

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
    void export_info(int tree_width, int remove_cnt, int true_num_nodes, ofstream& output, chrono::microseconds duration, int num_visited)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)"
             << " " << double(duration.count()) / 1000000 << endl;
        output << tree_width << " " << remove_cnt << " " << double(duration.count()) / 1000000 << " " << depth_of_tree << " " << (double)leaf_cnt / remove_cnt << " " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << " " << (double)remove_cnt / num_visited * 100 << endl;
    }

    void make_tree()
    {
        // initialize
        depth.resize(num_nodes, -1);
        parents.resize(num_nodes, -1);
        vector<int> child_cnt(num_nodes, 0);
        int num_core_child = 0;

        for (int i = 0; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            vector<int> nbrs = node_stack[i].second;

            // ouput <nd> <nbr 1> <nbr 2> ... <nbr n> <parent>
            int parent = -1; // the parent is itselft at first
            int max_depth = -1;
            sort(nbrs.begin(), nbrs.end());
            for (int nbr : nbrs)
                if (depth[nbr] > max_depth) {
                    max_depth = depth[nbr];
                    parent = nbr;
                }
            depth[nd] = max_depth + 1;
            if (max_depth == -1)
                num_core_child++;
            else {
                parents[nd] = parent;
                child_cnt[parent]++;
            }
        }

        depth_of_tree = 0;
        leaf_cnt = 0;
        total_child_cnt = 0;
        for (int i = 0; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            if (depth[nd] > depth_of_tree)
                depth_of_tree = depth[nd];
            if (child_cnt[nd] == 0)
                leaf_cnt++;
            total_child_cnt += child_cnt[nd];
        }
    }

    void print_stack()
    {
        string output_name = "tree/" + type + "-" + to_string(max_tree_width) + "-" + filename + ".tree";
        ofstream tree_output(output_name);
        int start = 0;
        // decide whether there is a core or not
        if (remove_cnt == true_num_nodes) {
            // print root node in the tree
            int root = node_stack[0].first;
            vector<int> root_nbrs = node_stack[0].second;
            tree_output << root << endl;
            sort(root_nbrs.begin(), root_nbrs.end());
            for (int nbr : root_nbrs)
                tree_output << nbr << " ";
            tree_output << endl;
            tree_output << "root" << endl;
            start = 1;
        } else {
            tree_output << "core" << endl;
            tree_output << endl;
            tree_output << "root" << endl;
        }

        for (int i = start; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            vector<int> nbrs = node_stack[i].second;

            // ouput <nd> <nbr 1> <nbr 2> ... <nbr n> <parent>
            tree_output << nd << endl;
            for (int nbr : nbrs) {
                tree_output << nbr << " ";
            }
            tree_output << endl;
            tree_output << parents[nd] << endl;
        }
    }

    void add_to_stack(int nd, vector<int> nbrs)
    {
        vector<int> new_nbrs;
        for (int nbr : nbrs)
            if (nbr != nd)
                new_nbrs.push_back(nbr);
        node_stack.push_front(make_pair(nd, new_nbrs));
    }
};