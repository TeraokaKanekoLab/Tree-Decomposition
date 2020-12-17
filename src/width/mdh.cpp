#include "../mdh.h"

class mdh_graph : public mdh {
public:
    void decompose()
    {
        string output_name = "output/mdh-" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream output(output_name);
        int crnt_deg = 1;
        priority_queue<node, vector<node>, greater<node>> degreeq;

        // counts vertices with edges (exclude non-edged vertex)
        // initialize priority queue
        for (int i = 0; i < neighbors_of.size(); ++i) {
            int deg = neighbors_of[i].size();
            if (deg) {
                true_num_nodes++;
                degreeq.push(node(deg, i));
            }
        }
        output << true_num_nodes << endl;
        auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size())
                continue; // outdated entry in degreeq
            if (deg > crnt_deg) {
                end = std::chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                make_tree();
                export_info(output, crnt_deg, remove_cnt, true_num_nodes, int(duration.count()), true_num_nodes);
                crnt_deg = deg;
                start = std::chrono::steady_clock::now();
            }
            if (deg > max_tree_width)
                break;
            vector<int> nbrs;
            for (int nbr : neighbors_of[nd])
                nbrs.push_back(nbr);
            clique(nbrs);
            for (int nbr : nbrs) {
                neighbors_of[nbr].erase(nd);
                degreeq.push(node(neighbors_of[nbr].size(), nbr));
            }
            add_to_stack(nd, nbrs);
            neighbors_of.erase(nd);
            remove_cnt++;
        }
        if (remove_cnt == true_num_nodes) {
            end = std::chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
            make_tree();
            export_info(output, crnt_deg, remove_cnt, true_num_nodes, int(duration.count()), true_num_nodes);
        }
        output.close();
        cout << "result written to " << output_name << endl;
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }

    type = "mdh";
    filename = argv[1];
    mdh_graph g;
    g.max_tree_width = stoi(argv[2]);
    g.read_edges();
    g.make_graph();
    g.decompose();
    // g.print_stack();

    return 0;
}
