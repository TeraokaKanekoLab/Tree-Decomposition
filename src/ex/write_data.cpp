#include "../betweenness_centrality.hpp"
#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = "1000000";

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();

    string output_name = "output/" + filename + ".csv";
    ofstream output(output_name);

    for (auto bc_key_value : bcs) {
        int nd = bc_key_value.first;
        double bc = bc_key_value.second;
        int induce = t.subtree_size_induced_by(nd);
        int dl = t.dist_from_leaf(nd);
        bool in_main = t.is_in_mainstream(nd);
        output << nd << "," << bc << "," << induce << "," << dl << "," << in_main << endl;
    }

    return 0;
}
