#include "../sbr.h"

class sbr_graph : public sbr {
public:
    void decompose()
    {
        int tree_width = 1;
        parent.resize(num_nodes);
        priority_queue<node, vector<node>, greater<node>> Q;
        string output_name = "step/sbr-" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream output(output_name);

        for (int nd = 0; nd < num_nodes; ++nd) {
            parent[nd] = nd;
            Q.push(node(adj[nd].size(), nd));
        }

        int interval;
        if (true_num_nodes > 100)
            interval = true_num_nodes / 100;
        else
            interval = 1;
        while (!Q.empty() && tree_width < max_tree_width) {
            int deg = Q.top().first;
            int nd = Q.top().second;
            Q.pop();
            if (deg == 0)
                continue;
            vector<int> nbrs = neighbor(nd); // get all the neighbours
            int true_deg = (int)nbrs.size() - count(nbrs.begin(), nbrs.end(), nd);

            if (true_deg > deg) { // if true degree is larger than the degree
                Q.push({ true_deg, nd });
                continue;
            }
            if (true_deg > tree_width)
                tree_width = true_deg;
            if (remove_cnt % interval == 0) { // some condition
                make_tree();
                export_info_step(output, true_deg, remove_cnt, true_num_nodes, 0, 0);
            }
            remove_cnt++;
            add_to_stack(nd, nbrs);
            contract(nd);
        }
        make_tree();
        export_info_step(output, 0, remove_cnt, true_num_nodes, 0, 0);
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

    sbr_graph g;
    filename = argv[1];
    type = "sbr";
    g.max_tree_width = stoi(argv[2]);
    g.read_edges();
    g.make_graph();
    g.decompose();
    // g.print_stack();

    return 0;
}
