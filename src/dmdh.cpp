#include "mdh.h"

class dmdh : public mdh {
public:
    void decompose(int max_tree_width, ofstream& output)
    {
        int tree_width = 1;
        priority_queue<node, vector<node>, greater<node>> degreeq;
        vector<bool> visited(num_nodes, false);
        for (auto nd : neighbors_of)
            if (nd.second.size())
                true_num_nodes++;

        auto start = std::chrono::steady_clock::now();
        // start with the first node of the first edge.
        int nd = edges[0].first;
        visited[nd] = true;
        degreeq.push(node(neighbors_of[nd].size(), nd));
        // print_priority_queue(degreeq);

        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            bool should_stop = true;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size()) {
                // print_priority_queue(degreeq);
                continue; // outdated entry in degreeq
            }

            // create neighbor array
            vector<int> nbrs;
            int min_deg = deg;
            int min_deg_nb = nd;
            for (int nbr : neighbors_of[nd]) {
                nbrs.push_back(nbr);
                if (neighbors_of[nbr].size() < min_deg) {
                    min_deg = neighbors_of[nbr].size();
                    min_deg_nb = nbr;
                }
            }
            if (deg > max_tree_width || min_deg_nb != nd) {
                degreeq.push(node(deg, nd));
                for (int nbr : nbrs) {
                    if (!visited[nbr]) {
                        visited[nbr] = true;
                        degreeq.push(node(neighbors_of[nbr].size(), nbr));
                        should_stop = false;
                    }
                }
            } else {
                clique(nbrs);
                should_stop = false;
                for (int nbr : nbrs) {
                    neighbors_of[nbr].erase(nd);
                    visited[nbr] = true;
                    degreeq.push(node(neighbors_of[nbr].size(), nbr));
                }
                add_to_stack(nd, nbrs);
                neighbors_of.erase(nd);
                remove_cnt++;
            }
            // print_priority_queue(degreeq);
            if (should_stop) {
                break;
            }
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        make_tree();
        int ret_cnt = 0;
        for (bool is_ret : visited)
            if (is_ret)
                ret_cnt++;
        export_info(max_tree_width, remove_cnt, true_num_nodes, output, duration, ret_cnt);
    }
};

void copy_master(dmdh& g, dmdh& master)
{
    g.num_nodes = master.num_nodes; // This value may be different from the official number of nodes.
    g.true_num_nodes = master.true_num_nodes;
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
    type = "dmdh";
    string output_name = "output/" + type + "-" + to_string(max_width) + "-" + filename + ".output";
    ofstream output(output_name);
    dmdh master;
    master.read_edges();
    for (int width = 0; width < max_width;) {
        if (width < 10)
            width++;
        else
            width += width / 10;
        if (width >= max_width)
            width = max_width;
        dmdh g;
        copy_master(g, master);
        g.decompose(width, output);
        // if (width == max_width) {
        //     g.max_tree_width = width;
        //     g.print_stack();
        // }
    }
    // master.decompose(max_width, output);
    output.close();
    cout << "result written to " << output_name << endl;

    return 0;
}