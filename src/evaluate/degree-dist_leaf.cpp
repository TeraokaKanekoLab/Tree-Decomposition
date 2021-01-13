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
    vector<int> bags = t.all_bags();

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    string output_name = "output/degree-dist_leaf/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bag : bags) {
        int dl = t.dist_from_leaf(bag);
        int deg = g.degree(bag);
        output << dl << " " << deg << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}