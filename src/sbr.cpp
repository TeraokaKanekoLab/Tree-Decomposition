#include "sbr.h"

class sbr_graph : public sbr {
public:
    void decompose(int max_tree_width)
    {
        int tree_width = 1;
        parent.resize(num_nodes);
        priority_queue<node, vector<node>, greater<node>> Q;
        int remove_cnt = 0;
        string output_name = "output/sbr-" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream output(output_name);
        chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        for (int u = 0; u < num_nodes; ++u) {
            parent[u] = u;
            Q.push(node(adj[u].size(), u));
        }

        while (!Q.empty() && tree_width < max_tree_width) {
            int deg = Q.top().first;
            int u = Q.top().second;
            Q.pop();
            if (deg == 0)
                continue;
            vector<int> nbh = neighbor(u); // get all the neighbours
            int true_deg = (int)nbh.size();

            if (true_deg > deg) { // if true degree is larger than the degree
                Q.push({ true_deg, u });
                continue;
            }
            // print_neighbor(u, nbh);
            if (true_deg > tree_width) {
                // when we come here, the last chrono::steady_clock::time_point& end
                // is the end of the execution with the tree_width
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                export_info(tree_width, remove_cnt, true_num_nodes, output, duration);
                tree_width = true_deg;
                start = end;
            }
            remove_cnt++;
            end = std::chrono::steady_clock::now();
            contract(u);
        }
        end = std::chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        export_info(tree_width, remove_cnt, true_num_nodes, output, duration);
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
    g.read_edges();
    g.make_graph();

    g.decompose(stoi(argv[2]));

    return 0;
}
