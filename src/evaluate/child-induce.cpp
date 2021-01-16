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
    vector<int> all_bags = t.all_bags();

    string output_name = "output/child-induce/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bag : all_bags) {
        int child = t.num_children(bag);
        int induce = t.subtree_size_induced_by(bag);
        output << induce << " " << child << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}