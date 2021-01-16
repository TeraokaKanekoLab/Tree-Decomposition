#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 1000

vector<pair<double, int>> bc_index(vector<pair<int, double>> index_bc)
{
    vector<pair<double, int>> bcs;
    for (auto bc : index_bc)
        bcs.push_back(make_pair(bc.second, bc.first));
    sort(bcs.begin(), bcs.end(), greater<pair<double, int>>());
    return bcs;
}

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
    vector<int> all_bags = t.all_bags();

    string output_name = "output/induce-degree/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (int bag : all_bags) {
        int subtree = t.subtree_size_induced_by(bag);
        int deg = g.degree(bag);

        output << deg << " " << subtree << endl;
    }

    return 0;
}