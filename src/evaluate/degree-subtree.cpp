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

    string output_name = "output/degree-subtree/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bag : bags) {
        int ss = t.subtree_size(bag);
        int deg = g.degree(bag);
        output << ss << " " << deg << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}