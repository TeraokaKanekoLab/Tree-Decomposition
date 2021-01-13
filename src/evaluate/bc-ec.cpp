#include "../betweenness_centrality.hpp"
#include "../eccentricity.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Eccentricity e;
    string path_to_e = "data/eccentricity/" + filename + ".ec";
    e.read_eccentricity(path_to_e);
    vector<pair<int, int>> ecs = e.get_eccentricity();
    sort(ecs.begin(), ecs.end());

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<int, double>> bcs = b.get_betweenness_centrality();
    sort(bcs.begin(), bcs.end());

    string output_name = "output/bc-ec/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (int i = 0; i < ecs.size(); ++i) {
        int ec = ecs[i].second;
        double bc = bcs[i].second;
        output << ec << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}