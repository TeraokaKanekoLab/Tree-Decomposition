#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();
    string output_name = "output/bc-cc/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto bc : bcs) {
        double cc = g.compute_clustering_coefficient(bc.first);
        output << cc << " " << bc.second << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}