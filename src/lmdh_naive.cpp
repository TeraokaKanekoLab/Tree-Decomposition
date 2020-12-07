#include "mdh.h"

class lmdh_graph : public mdh {
public:
    void decompose(int max_tree_width, ofstream& output)
    {
        int tree_width = 1;
        priority_queue<node, vector<node>, greater<node>> degreeq;
        vector<bool> retrieved(num_nodes, false);
        for (auto nd : neighbors_of)
            if (nd.second.size())
                true_num_nodes++;

        // start with the first node of the first edge.
        int nd = edges[0].first;
        retrieved[nd] = true;
        degreeq.push(node(neighbors_of[nd].size(), nd));

        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            bool should_stop = true;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size())
                continue; // outdated entry in degreeq

            // create neighbor array
            vector<int> nbrs;
            for (int nbr : neighbors_of[nd])
                nbrs.push_back(nbr);
            if (deg > max_tree_width) {
                degreeq.push(node(deg, nd));
                for (int nbr : nbrs) {
                    if (!retrieved[nbr]) {
                        retrieved[nbr] = true;
                        degreeq.push(node(neighbors_of[nbr].size(), nbr));
                        should_stop = false;
                    }
                }
            } else {
                clique(nbrs);
                should_stop = false;
                for (int nbr : nbrs) {
                    neighbors_of[nbr].erase(nd);
                    retrieved[nbr] = true;
                    degreeq.push(node(neighbors_of[nbr].size(), nbr));
                }
                add_to_stack(nd, nbrs);
                neighbors_of.erase(nd);
                remove_cnt++;
            }
            if (should_stop) {
                break;
            }
        }
        export_info(max_tree_width, remove_cnt, true_num_nodes, output);
        int ret_cnt = 0;
        for (bool is_ret : retrieved)
            if (is_ret)
                ret_cnt++;
        cout << "retrived nodes: " << ret_cnt << endl;
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
    g.edges = master.edges;
    g.make_graph();
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }
    filename = argv[1];
    int max_width = stoi(argv[2]);
    type = "lmdh_naive";
    string output_name = "output/" + type + "-" + to_string(max_width) + "-" + filename + ".output";
    ofstream output(output_name);
    lmdh_graph master;
    master.read_edges();
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

    // master.make_graph();
    // master.decompose(max_width, output);
    // master.max_tree_width = max_width;
    // master.print_stack();

    output.close();
    cout << "result written to " << output_name << endl;

    return 0;
}
