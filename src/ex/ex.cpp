#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = "5";

    // Graph g;
    // g.read_graph("graph/fb-pages-artist.gr");

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    vector<int> bags = t.all_bags();
    for (int bag : bags)
        cout << bag << ": " << t.subtree_size(bag) << endl;

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");

    return 0;
}
