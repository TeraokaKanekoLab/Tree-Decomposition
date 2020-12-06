#include "sbr.h"

class lmdh_graph : public sbr {
public:
    void decompose(int max_tree_width, ofstream& output)
    {
        int tree_width = 1;
        parent.resize(num_nodes);
        priority_queue<node, vector<node>, greater<node>> Q;
        vector<bool> retrieved;

        for (int u = 0; u < num_nodes; ++u) {
            parent[u] = u;
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

            vector<int> nbrs = neighbor(u); // get all the neighbours
            int true_deg = (int)nbrs.size() - count(nbrs.begin(), nbrs.end(), u);
            int num_remove = 0;
            // add its neighbors to the push as known nodes
            if (true_deg > max_tree_width) {
                Q.push(node(true_deg, u));
            } else {
                // cout << "node " << u << " removed with width " << true_deg << endl;
                contract(u);
                remove_cnt++;
                add_to_stack(u, nbrs);
            }
            for (int nb : nbrs)
                if (!retrieved[nb]) {
                    retrieved[nb] = true;
                    Q.push(node(adj[nb].size(), nb));
                    num_remove++;
                }
            if (true_deg > max_tree_width && deg == true_deg && num_remove == 0)
                break;
        }
        export_info(max_tree_width, remove_cnt, true_num_nodes, output);
    }

    void export_info(int tree_width, int remove_cnt, int true_num_nodes, ofstream& output)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)" << endl;
        output << tree_width << " " << remove_cnt << endl;
    }
};

void copy_master(lmdh_graph& g, lmdh_graph& master)
{
    g.num_nodes = master.num_nodes; // This value may be different from the official number of nodes.
    g.true_num_nodes = master.true_num_nodes;
    g.adj = master.adj;
    g.edges = master.edges;
    g.parent = master.parent;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }
    filename = argv[1];
    int max_width = stoi(argv[2]);
    type = "lmdh_sbr";
    string output_name = "output/" + type + "-" + to_string(max_width) + "-" + filename + ".output ";
    ofstream output(output_name);
    lmdh_graph master;
    master.read_edges();
    master.make_graph();
    for (int width = 0; width < max_width;) {
        if (width < 10)
            width++;
        else
            width += width / 10;
        if (width >= max_width)
            width = max_width;
        lmdh_graph g;
        copy_master(g, master);
        g.decompose(width, output);
        if (width == max_width) {
            g.max_tree_width = max_width;
            g.print_stack();
        }
    }
    // step(master, 3, output);
    output.close();
    cout << "result written to " << output_name << endl;

    return 0;
}