#include "../betweenness_centrality.hpp"
#include "../fillin.hpp"
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

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);
    vector<int> eccentricities = t.get_eccentricities();

    Fillin f;
    string path_to_f = "data/fillin/" + filename + ".fl";
    f.read_fillin(path_to_f);
    vector<pair<int, double>> fillins = f.get_fillins();

    string output_name = "output/bc-fillin/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto fillin : fillins) {
        int nd = fillin.first;
        double fl = fillin.second;
        double bc = b.betweenness_centrality_of(nd);
        output << fl << " " << bc << " " << g.degree(nd) << " " << t.subtree_size_induced_by(nd) << " " << g.compute_clustering_coefficient(nd) << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}