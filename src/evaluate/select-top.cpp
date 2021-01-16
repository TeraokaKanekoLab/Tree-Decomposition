#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 1000

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
    string filename = argv[1];
    string width = argv[2];

    Graph g;
    string path_to_g = "graph/" + filename + ".gr";
    g.read_graph(path_to_g);

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);

    Betweenness_centrality b;
    string path_to_b = "data/betweenness_centrality/" + filename + ".bc";
    b.read_betweenness_centrality(path_to_b);
    vector<pair<double, int>> bcs = bc_index(b.get_betweenness_centrality());

    string output_name = "output/select-top/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    vector<pair<int, int>> sorted_by_size;
    for (int bag : t.all_bags())
        // if (t.is_in_mainstream(bag))
        // sorted_by_size.push_back(make_pair(t.subtree_size_induced_by(bag), bag));
        sorted_by_size.push_back(make_pair(t.dist_from_leaf(bag), bag));
    // sorted_by_size.push_back(make_pair(g.degree(bag), bag));
    // sorted_by_size.push_back(make_pair(t.num_children(bag), bag));

    int num_bags = t.num_bags();

    sort(sorted_by_size.begin(), sorted_by_size.end(), greater<pair<int, int>>());
    auto first = sorted_by_size.begin();
    auto last = sorted_by_size.begin() + num_bags * 1 / 100; // 1%
    vector<pair<int, int>> top1(first, last);
    last = sorted_by_size.begin() + num_bags * 5 / 100; // 5%
    vector<pair<int, int>> top5(first, last);
    last = sorted_by_size.begin() + num_bags * 10 / 100; // 10%
    vector<pair<int, int>> top10(first, last);
    last = sorted_by_size.begin() + num_bags * 15 / 100; // 15%
    vector<pair<int, int>> top15(first, last);
    last = sorted_by_size.begin() + num_bags * 20 / 100; // 20%
    vector<pair<int, int>> top20(first, last);
    last = sorted_by_size.begin() + num_bags * 25 / 100; // 25%
    vector<pair<int, int>> top25(first, last);

    int index = 0;
    unordered_set<int> top_bags;
    vector<double> cnta1, cnta5, cnta10, cnta15, cnta20, cnta25;
    for (int per = 1; per <= SAMPLE; ++per) {
        for (; index < t.num_bags() * per / SAMPLE; ++index)
            top_bags.insert(bcs[index].second);

        int cnt1 = 0;
        for (auto node : top1)
            if (top_bags.find(node.second) != top_bags.end())
                cnt1++;
        int cnt5 = 0;
        for (auto node : top5)
            if (top_bags.find(node.second) != top_bags.end())
                cnt5++;
        int cnt10 = 0;
        for (auto node : top10)
            if (top_bags.find(node.second) != top_bags.end())
                cnt10++;
        int cnt15 = 0;
        for (auto node : top15)
            if (top_bags.find(node.second) != top_bags.end())
                cnt15++;
        int cnt20 = 0;
        for (auto node : top20)
            if (top_bags.find(node.second) != top_bags.end())
                cnt20++;
        int cnt25 = 0;
        for (auto node : top25)
            if (top_bags.find(node.second) != top_bags.end())
                cnt25++;
        cnta1.push_back((double)cnt1 / top1.size() * 100);
        cnta5.push_back((double)cnt5 / top5.size() * 100);
        cnta10.push_back((double)cnt10 / top10.size() * 100);
        cnta15.push_back((double)cnt15 / top15.size() * 100);
        cnta20.push_back((double)cnt20 / top20.size() * 100);
        cnta25.push_back((double)cnt25 / top25.size() * 100);
        output << (double)per / SAMPLE * 100 << " " << (double)cnt1 / top1.size() * 100 << " " << (double)cnt5 / top5.size() * 100 << " " << (double)cnt10 / top10.size() * 100 << " " << (double)cnt15 / top15.size() * 100 << " " << (double)cnt20 / top20.size() * 100 << " " << (double)cnt25 / top25.size() * 100 << " " << endl;
    }

    return 0;
}