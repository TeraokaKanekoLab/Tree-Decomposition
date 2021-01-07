#include "../sbr.h"

class sbr_graph : public sbr {
public:
    void decompose()
    {
        int tree_width = 1;
        parent.resize(num_nodes);
        priority_queue<node, vector<node>, greater<node>> Q;
        string output_name = "output/width/sbr-" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream output(output_name);
        chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        for (int nd = 0; nd < num_nodes; ++nd) {
            parent[nd] = nd;
            Q.push(node(adj[nd].size(), nd));
        }

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
            // print_neighbor(u, nbrs);
            if (true_deg > tree_width) {
                // when we come here, the last chrono::steady_clock::time_point& end
                // is the end of the execution with the tree_width
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                make_tree();
                export_info(output, tree_width, remove_cnt, true_num_nodes, int(duration.count()), true_num_nodes);
                tree_width = true_deg;
                start = std::chrono::steady_clock::now();
            }
            remove_cnt++;
            end = std::chrono::steady_clock::now();
            add_to_stack(nd, nbrs);
            contract(nd);
        }
        end = std::chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        make_tree();
        export_info(output, tree_width, remove_cnt, true_num_nodes, int(duration.count()), true_num_nodes);
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
    g.print_depth_bagsize();

    return 0;
}
