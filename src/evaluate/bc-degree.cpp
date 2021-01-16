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
    sort(bcs.begin(), bcs.end());

    string output_name = "output/bc-degree/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (int i = 0; i < bcs.size(); ++i) {
        int nd = bcs[i].first;
        int deg = g.degree(nd);
        double bc = bcs[i].second;
        if (deg == 1)
            continue;
        output << deg << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}