#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

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
    vector<int> eccentricities = t.get_eccentricities();

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();

    string output_name = "output/bc-mainstream/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    int num_mainstream = 0;
    int num_non_mainstream = 0;
    for (auto bc_pair : bcs) {
        int nd = bc_pair.first;
        double bc = bc_pair.second;
        bool is_in_mainstream = t.is_in_mainstream(nd);
        if (is_in_mainstream)
            num_mainstream++;
        else
            num_non_mainstream++;
        output << is_in_mainstream << " " << bc << " " << g.degree(nd) << endl;
    }
    cout << "** mainstream: " << num_mainstream << " (" << (double)num_mainstream / (num_mainstream + num_non_mainstream) * 100 << "%)" << endl;
    cout << "non-mainstream : " << num_non_mainstream << "(" << (double)num_non_mainstream / (num_mainstream + num_non_mainstream) * 100 << " %) " << endl;
    cout << "result written to " << output_name << endl;

    return 0;
}