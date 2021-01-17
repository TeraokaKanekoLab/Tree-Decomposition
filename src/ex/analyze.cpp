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
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <width>" << endl;
    }
    string filename = argv[1];
    string width = argv[2];

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

    vector<pair<int, int>> by_size;
    vector<pair<int, int>> by_dist;
    vector<pair<int, int>> by_degree;
    vector<pair<int, int>> by_size_degree;
    for (int bag : t.all_bags()) {
        by_size.push_back(make_pair(t.subtree_size_induced_by(bag), bag));
        by_dist.push_back(make_pair(t.dist_from_leaf(bag), bag));
        by_degree.push_back(make_pair(g.degree(bag), bag));
        by_size_degree.push_back(make_pair(2 * t.subtree_size_induced_by(bag) - g.degree(bag), bag));
    }
    sort(by_size.begin(), by_size.end(), greater<pair<int, int>>());
    sort(by_dist.begin(), by_dist.end(), greater<pair<int, int>>());
    sort(by_degree.begin(), by_degree.end(), greater<pair<int, int>>());
    sort(by_size_degree.begin(), by_size_degree.end(), greater<pair<int, int>>());
    vector<int> size_rank(array_size, 0);
    vector<int> dist_rank(array_size, 0);
    vector<int> degree_rank(array_size, 0);
    vector<int> bc_rank(array_size, 0);

    for (int i = 0; i < bcs.size(); ++i) {
        size_rank[by_size[i].second] = i + 1;
        dist_rank[by_dist[i].second] = i + 1;
        degree_rank[by_degree[i].second] = i + 1;
        bc_rank[bcs[i].second] = i + 1;
    }

    cout << "|node id|degree|average degree of neighbors|degree rank|ISS rank|central betweenness rank|clustering coefficient|" << endl;
    cout << "|:--:|:--:|:--:|:--:|:--:|:--:|:--:|" << endl;
    for (int i = 0; i < bcs.size(); ++i) {
        int nd = bcs[i].second;
        double cc = g.compute_clustering_coefficient(nd);
        cout << "|" << nd << "|" << g.degree(nd) << "|" << g.average_degree_of_neighbors(nd) << "|" << degree_rank[nd] << "|" << size_rank[nd] << "|" << bc_rank[nd] << "|" << cc << "|" << endl;
    }

    return 0;
}
