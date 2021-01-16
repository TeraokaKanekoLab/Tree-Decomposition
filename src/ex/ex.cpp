#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    // string width = "1000000";
    string width = "3";

    Graph g;
    g.read_graph("graph/" + filename + ".gr");

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    vector<int> bags = t.all_bags();

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");

    // Eccentricity e;
    // e.read_eccentricity("data/eccentricity/" + filename + ".eccentricity");
    // vector<pair<int, int>> eccs = e.get_eccentricity();

    for (int bag : t.all_bags()) {
        cout << "node " << bag << ": " << t.compute_betweenness_centrality(bag) << endl;
        }

    return 0;
}
