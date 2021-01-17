#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = "1000000";
    // string width = "3";

    Graph g;
    g.read_graph("graph/" + filename + ".gr");

    Tree_Decomposition t;
    cout << "loading..." << endl;
    t.read_tree("tree/" + width + "-" + filename + ".tree");
    vector<int> bags = t.all_bags();

    // Communities c;
    // c.read_community("graph/community/com-amazon.cm");

    // Eccentricity e;
    // e.read_eccentricity("data/eccentricity/" + filename + ".eccentricity");
    // vector<pair<int, int>> eccs = e.get_eccentricity();

    vector<int> candidates { 53213, 35290, 38109, 1086 };
    for (int cand : candidates) {
        string output_name = "output/nbr-deg/" + to_string(cand) + "-" + filename + ".output";
        ofstream output(output_name);
        vector<int> nbrs = g.neighbors(cand);
        int sum_deg = 0;
        int max_deg = 0;
        for (int nbr : nbrs) {
            if (g.degree(nbr) > max_deg)
                max_deg = g.degree(nbr);
        }
        vector<int> num_nodes_of_degree(max_deg + 1, 0);
        for (int nbr : nbrs) {
            num_nodes_of_degree[g.degree(nbr)]++;
        }
        int all = 0;
        for (int i = 0; i < num_nodes_of_degree.size(); ++i) {
            all += num_nodes_of_degree[i];
            output << i << " " << all << endl;
            // output << i << " " << num_nodes_of_degree[i] << endl;
        }
        output.close();
    }

    return 0;
}
