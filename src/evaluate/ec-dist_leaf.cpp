#include "../eccentricity.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);
    vector<int> eccentricities = t.get_eccentricities();

    Eccentricity e;
    string path_to_e = "data/eccentricity/" + filename + ".eccentricity";
    e.read_eccentricity(path_to_e);
    vector<pair<int, int>> ecs = e.get_eccentricity();

    string output_name = "output/ec-dist_leaf/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (auto ec_pair : ecs) {
        int nd = ec_pair.first;
        int ec = ec_pair.second;
        int dl = t.dist_from_leaf(nd);
        output << dl << " " << ec << endl;
    }
    cout << "result written to " << output_name << endl;

    return 0;
}