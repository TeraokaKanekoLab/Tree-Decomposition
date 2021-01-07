#include "../mdh.h"

class lmdh : public mdh {
public:
    void decompose(int limit, ofstream& output)
    {
        int tree_width = 1;
        priority_queue<node> degreeq;
        vector<bool> visited(num_nodes, false);
        int max_deg = 0;
        int max_deg_node = -1;
        for (int i = 0; i < neighbors_of.size(); ++i) {
            auto nd = neighbors_of[i];
            int deg = nd.size();
            if (deg)
                true_num_nodes++;
            if (deg > max_deg) {
                max_deg = deg;
                max_deg_node = i;
            }
        }
        // start from node with max degreee
        int nd = max_deg_node;
        visited[nd] = true;
        degreeq.push(node(neighbors_of[nd].size(), nd));

        while (!degreeq.empty() && remove_cnt < limit) {
            auto start = std::chrono::steady_clock::now();
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
            clique(nbrs);
            for (int nbr : nbrs) {
                neighbors_of[nbr].erase(nd);
                visited[nbr] = true;
                degreeq.push(node(neighbors_of[nbr].size(), nbr));
            }
            add_to_stack(nd, nbrs);
            neighbors_of.erase(nd);
            remove_cnt++;
            auto end = std::chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            make_tree();
            export_info_step(output, 0, remove_cnt, true_num_nodes, (int)duration.count(), 0);
        }
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <limit>" << endl;
        exit(-1);
    }
    filename = argv[1];
    int limit = stoi(argv[2]);
    type = "l-max-dh";
    string output_name = "output/l-max-dh/" + to_string(limit) + "-" + filename + ".output";
    ofstream output(output_name);
    lmdh master;
    master.read_edges();
    master.make_graph();
    master.decompose(limit, output);
    master.max_tree_width = limit;
    master.print_stack();

    output.close();
    cout << "result written to " << output_name << endl;

    return 0;
}
