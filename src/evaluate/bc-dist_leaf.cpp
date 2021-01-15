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

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();

    Graph g;
    g.read_graph("graph/" + filename + ".gr");

    string output_name = "output/bc-dist_leaf/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bc_pair : bcs) {
        int nd = bc_pair.first;
        double bc = bc_pair.second;
        int dl = t.dist_from_leaf(nd);
        // int dl = g.degree(nd);
        output << dl << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}