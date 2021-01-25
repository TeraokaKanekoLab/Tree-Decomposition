#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);
    vector<int> eccentricities = t.get_eccentricities();

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();

    string output_name = "output/bc-sum_strahler/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bc_pair : bcs) {
        int nd = bc_pair.first;
        double bc = bc_pair.second;
        int ss = 0;
        for (int child : t.children_of(nd))
            ss += t.compute_strahler(child);
        output << ss << " " << bc << " " << g.degree(nd) << " " << t.subtree_size_induced_by(nd) << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}