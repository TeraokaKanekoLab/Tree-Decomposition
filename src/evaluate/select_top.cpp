#include "../betweenness_centrality.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 10000

vector<pair<double, int>> bc_index(vector<pair<int, double>> index_bc)
{
    vector<pair<double, int>> bcs;
    for (auto bc : index_bc)
        bcs.push_back(make_pair(bc.second, bc.first));
    sort(bcs.begin(), bcs.end());
    return bcs;
}

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<double, int>> bcs = bc_index(b.get_betweenness_centrality());

    string output_name = "output/select_top/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    vector<pair<int, int>> sorted_by_size;
    for (int bag : t.all_bags()) {
        sorted_by_size.push_back(make_pair(t.subtree_size_induced_by(bag), bag));
    }

    vector<pair<int, int>> sorted_by_dist;
    for (int bag : t.all_bags()) {
        sorted_by_dist.push_back(make_pair(t.dist_from_leaf(bag), bag));
    }

    int top_size = TOP_PERCENTAGE * sorted_by_size.size() / 100;

    sort(sorted_by_size.begin(), sorted_by_size.end(), greater<pair<int, int>>());
    sorted_by_size.resize(top_size);
    sort(sorted_by_dist.begin(), sorted_by_dist.end(), greater<pair<int, int>>());
    sorted_by_dist.resize(top_size);

    int index = 0;
    unordered_set<int> top_bags;
    vector<double> cnt_size, cnt_dist;
    for (int per = 1; per <= SAMPLE; ++per) {
        for (; index < t.num_bags() * per / SAMPLE; ++index) {
            top_bags.insert(bcs[index].second);
        }
        int cnt1 = 0;
        for (auto node : sorted_by_size) {
            int nd = node.second;
            if (top_bags.find(nd) != top_bags.end())
                cnt1++;
        }
        int cnt2 = 0;
        for (auto node : sorted_by_dist) {
            int nd = node.second;
            if (top_bags.find(nd) != top_bags.end())
                cnt2++;
        }
        cnt_size.push_back(100 - (double)cnt1 / top_size * 100);
        cnt_dist.push_back(100 - (double)cnt2 / top_size * 100);
    }
    for (int per = 1; per <= SAMPLE; ++per) {
        output << (double)per / SAMPLE * 100 << " " << cnt_size[SAMPLE - per] << " " << cnt_dist[SAMPLE - per] << endl;
    }
    return 0;
}