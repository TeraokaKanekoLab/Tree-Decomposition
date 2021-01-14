#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = "1000000";

    Graph g;
    g.read_graph("graph/" + filename + ".gr");

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    // vector<int> bags = t.all_bags();
    // for (int bag : bags)
    //     cout << bag << ": " << t.subtree_size(bag) << endl;

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");

    Eccentricity e;
    e.read_eccentricity("data/eccentricity/" + filename + ".eccentricity");
    vector<pair<int, int>> eccs = e.get_eccentricity();

    vector<int> centers = g.compute_centers(eccs);

    for (int center : centers) {
        cout << center << ": " << t.num_children(center) << endl;
    }

    return 0;
}
