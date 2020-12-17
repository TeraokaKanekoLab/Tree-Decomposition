#include "../mdh.h"

class lmdh : public mdh {
public:
    void decompose(int max_tree_width, ofstream& output)
    {
        int tree_width = 1;
        priority_queue<node, vector<node>, greater<node>> degreeq;
        vector<bool> visited(num_nodes, false);
        for (auto nd : neighbors_of)
            if (nd.second.size())
                true_num_nodes++;

        // start with the first node of the first edge.
        int nd = edges[0].first;
        visited[nd] = true;
        degreeq.push(node(neighbors_of[nd].size(), nd));

        int interval = 10;

        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            bool should_stop = true;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size())
                continue; // outdated entry in degreeq

            if (remove_cnt % interval == 0) { // some condition
                make_tree();
                export_info_step(output, deg, remove_cnt, true_num_nodes, 0, 0);
            }
            // create neighbor array
            vector<int> nbrs;
            for (int nbr : neighbors_of[nd])
                nbrs.push_back(nbr);
            if (deg > max_tree_width) {
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
            if (should_stop) {
                break;
            }
        }
        make_tree();
        int ret_cnt = 0;
        for (bool is_ret : visited)
            if (is_ret)
                ret_cnt++;
        export_info_step(output, 0, remove_cnt, true_num_nodes, 0, 0);
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }
    filename = argv[1];
    int max_width = stoi(argv[2]);
    type = "lmdh";
    string output_name = "step/" + type + "-" + to_string(max_width) + "-" + filename + ".output";
    ofstream output(output_name);
    lmdh master;
    master.read_edges();
    master.make_graph();
    master.decompose(max_width, output);

    output.close();
    cout << "result written to " << output_name << endl;

    return 0;
}
