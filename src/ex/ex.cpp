#include "../betweenness_centrality.hpp"
#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

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
    // string width = "1000000";
    // string width = "5";
    string width = "10";

    Graph g;
    g.read_graph("graph/" + filename + ".gr");

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    vector<int> bags = t.all_bags();
    int array_size = t.get_array_size();

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");

    // Eccentricity e;
    // e.read_eccentricity("data/eccentricity/" + filename + ".eccentricity");
    // vector<pair<int, int>> eccs = e.get_eccentricity();

    Betweenness_centrality b;
    b.read_betweenness_centrality("data/betweenness_centrality/" + filename + ".bc");
    vector<pair<double, int>> bcs = bc_index(b.get_betweenness_centrality());
    int nd = 4636;
    cout << "node " << nd << ", order: " << t.get_remove_order_of(nd) << endl;
    cout << "node " << nd << ", width: " << t.compute_width(nd) << endl;

    return 0;
}
