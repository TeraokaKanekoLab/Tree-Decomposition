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

    string output_name = "output/cc-induce/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bag : t.all_bags()) {
        double cc = g.compute_clustering_coefficient(bag);
        int ss = t.subtree_size_induced_by(bag);
        output << ss << " " << cc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}