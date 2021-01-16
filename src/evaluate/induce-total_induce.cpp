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
    vector<int> eccentricities = t.get_eccentricities();

    string output_name = "output/induce-total_induce/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto nd : t.all_bags()) {
        int is = t.subtree_size_induced_by(nd);
        int ss = t.total_subtree_size_induced_by(nd);
        output << is << " " << ss << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}