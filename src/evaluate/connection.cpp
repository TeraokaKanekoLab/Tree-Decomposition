#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Graph g;
    string path_to_graph = "graph/" + filename + ".gr";
    g.read_graph(path_to_graph);

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);

    string output_name = "output/connection/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    vector<int> all_bags = t.all_bags();
    cout << "# of children of core: " << t.num_children_of_core() << endl;
    cout << "# of bags: " << t.num_bags() << endl;
    for (int bag : all_bags) {
        int connection_in_tree = t.num_children(bag) + 1; // children + parent
        int degree_in_graph = g.degree(bag);
        output << degree_in_graph << " " << connection_in_tree << endl;
    }

    return 0;
}