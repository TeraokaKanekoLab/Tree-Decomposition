#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    // Graph g;
    // g.read_graph("graph/fb-pages-artist.gr");
    // g.read_graph("graph/fb-pages-tvshow.gr");
    // g.read_graph("graph/ca-CondMat.gr");
    // g.read_graph("graph/fb-pages-food.gr");
    // g.read_graph("graph/soc-karate.gr");
    // g.read_graph("graph/soc-flickr.gr");
    // g.read_graph("graph/ca-GrQc.gr");
    // if (argc != 2) {
    //     cout << argv[0] << " <filename>" << endl;
    //     return 0;
    // }
    // string filename = argv[1];
    // g.read_graph("graph/" + filename + ".gr");

    // // cout << "eccentricity(" << nd1 << ") = " << g.compute_eccentricity(nd1) << endl;
    // // cout << "clustering_coefficient(" << nd1 << ") = " << g.compute_clustering_coefficient(nd1) << endl;
    // cout << "average_clustering() = " << g.compute_average_clustering() << endl;
    // cout << "num_nodes() = " << g.get_num_nodes() << endl;
    // cout << "num_edges() = " << g.get_num_edges() << endl;
    // // print_vector_with_index(g.k_core());
    // vector<int> k_core = g.k_core();
    // cout << "find_max_degree() = " << g.find_max_degree() << endl;
    // cout << "average_degree = " << g.compute_average_degree() << endl;
    // cout << "max_k_core = " << *max_element(k_core.begin(), k_core.end()) << endl;
    // cout << "average_k_core = " << g.average_k_core() << endl;

    string filename = "prefectures";
    string width = "5";
    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    cout << "calculating..." << endl;
    vector<int> eccecntricities = t.get_eccentricities();
    cout << "size = " << eccecntricities.size() << endl;
    print_vector_with_index(eccecntricities);

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");
    // vector<vector<int>> cms = c.get_communities();
    // for (auto cm : cms) {
    //     double d = t.average_dist_in_group(cm);
    //     cout << "community: ";
    //     print_vector(cm);
    //     cout << "average dist = " << d << endl;
    // }

    return 0;
}
