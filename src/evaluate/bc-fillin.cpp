#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);
    vector<int> eccentricities = t.get_eccentricities();

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();

    string output_name = "output/bc-fillin/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bc_pair : bcs) {
        int nd = bc_pair.first;
        double bc = bc_pair.second;
        vector<int> nodes_in_bag = t.get_nodes_in_bag(nd);
        int sum = 0;
        int size = nodes_in_bag.size();
        for (int i = 0; i < size - 1; ++i)
            for (int j = i + 1; j < size; ++j)
                if (g.has_edge(nodes_in_bag[i], nodes_in_bag[j]))
                    sum++;

        if (size < 2) {
            continue;
        }
        output << (double)sum * 2 / (size * (size - 1)) << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}