#include "../betweenness_centrality.hpp"
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

    string output_name = "output/bc-width/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bc_pair : bcs) {
        int nd = bc_pair.first;
        double bc = bc_pair.second;
        int width = t.compute_width(nd);
        output << width << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}