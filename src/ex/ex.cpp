#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    // Graph g;
    // g.read_graph("graph/com-amazon.gr");

    // int nd1 = 548280, nd2 = 34;
    // // cout << "eccentricity(" << nd1 << ") = " << g.compute_eccentricity(nd1) << endl;
    // // cout << "clustering_coefficient(" << nd1 << ") = " << g.compute_clustering_coefficient(nd1) << endl;
    // cout << "average_clustering() = " << g.compute_average_clustering() << endl;

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/500-com-amazon.tree");
    cout << "calculating..." << endl;

    Communities c;
    c.read_community("graph/community/com-amazon.cm");
    vector<vector<int>> cms = c.get_communities();
    for (auto cm : cms) {
        double d = t.average_dist_in_group(cm);
        cout << "community: ";
        print_vector(cm);
        cout << "average dist = " << d << endl;
    }

    return 0;
}