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

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    string output_name = "output/child-degree/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto nd : t.all_bags()) {
        int num_children = t.num_children(nd);
        int deg = g.degree(nd);
        output << deg << " " << num_children << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}