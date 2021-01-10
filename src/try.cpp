#include "mdh.hpp"

class mdh_graph : public mdh {
public:
    void decompose()
    {
        string output_name = "output/width/try-" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream output(output_name);
        int crnt_deg = 1;
        auto comp = [&](node a, node b) {
            if (a.first != b.first)
                return a.first > b.first;
            return initial_degree[a.second] > initial_degree[b.second];
        };
        priority_queue<node, vector<node>, decltype(comp)> degreeq(comp);
        // priority_queue<node, vector<node>, greater<node>> degreeq;

        // counts vertices with edges (exclude non-edged vertex)
        // initialize priority queue
        for (int i = 0; i < neighbors_of.size(); ++i) {
            int deg = neighbors_of[i].size();
            initial_degree.push_back(deg);
            if (deg) {
                true_num_nodes++;
                degreeq.push(node(deg, i));
            }
        }
        output << true_num_nodes << endl;
        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size())
                continue; // outdated entry in degreeq
            if (deg > crnt_deg) {
                make_tree();
                crnt_deg = deg;
            }
            if (deg > max_tree_width)
                break;
            vector<int> nbrs;
            for (int nbr : neighbors_of[nd])
                nbrs.push_back(nbr);
            for (int nbr : nbrs) {
                neighbors_of[nbr].erase(nd);
                degreeq.push(node(neighbors_of[nbr].size(), nbr));
            }
            add_to_stack(nd, nbrs);
            neighbors_of.erase(nd);
            remove_cnt++;
        }
        if (remove_cnt == true_num_nodes) {
            make_tree();
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

    filename = argv[1];
    mdh_graph g;
    g.max_tree_width = stoi(argv[2]);
    g.read_edges();
    g.make_graph();
    g.decompose();
    g.print_stack();
    g.print_depth_bagsize();

    return 0;
}
