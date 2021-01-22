#include "../betweenness_centrality.hpp"
#include "../fillin.hpp"
#include "../graph.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);

    Fillin f;
    string path_to_f = "data/fillin/" + filename + ".fl";
    f.read_fillin(path_to_f);
    vector<pair<int, double>> fillins = f.get_fillins();

    string output_name = "output/bc-fillin/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto fillin : fillins) {
        int nd = fillin.first;
        double fl = fillin.second;
        double bc = b.betweenness_centrality_of(nd);
        output << fl << " " << bc << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}