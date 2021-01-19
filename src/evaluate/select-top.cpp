#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 1000

struct node {
    node(int id, int bs, int mt, bool it)
    {
        node_id = id;
        bagsize = bs;
        metric = mt;
        is_tree = it;
    }
    int node_id;
    int bagsize;
    int metric;
    bool is_tree;
};

bool sort_by_metric(const node& l, const node& r)
{
    if (l.metric != r.metric || !l.is_tree)
        return l.metric > r.metric;
    return l.bagsize > r.bagsize;
}

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

    vector<node> sorted_by_size;
    for (int bag : t.all_bags())
        // if (t.is_in_mainstream(bag))
        sorted_by_size.push_back(node(bag, t.bagsize_of(bag), t.subtree_size_induced_by(bag), true));
    // sorted_by_size.push_back(make_pair(t.dist_from_leaf(bag), bag));
    // sorted_by_size.push_back(make_pair(g.degree(bag), bag));
    // sorted_by_size.push_back(make_pair(2 * t.subtree_size_induced_by(bag) - g.degree(bag), bag));
    // sorted_by_size.push_back(make_pair(t.num_children(bag), bag));

    int num_bags = t.num_bags();

    sort(sorted_by_size.begin(), sorted_by_size.end(), sort_by_metric);
    auto first = sorted_by_size.begin();
    auto last = sorted_by_size.begin() + num_bags * 1 / 100; // 0.1%
    vector<node> top1(first, last);
    last = sorted_by_size.begin() + num_bags * 5 / 100; // 5%
    vector<node> top5(first, last);
    last = sorted_by_size.begin() + num_bags * 10 / 100; // 10%
    vector<node> top10(first, last);
    last = sorted_by_size.begin() + num_bags * 15 / 100; // 15%
    vector<node> top15(first, last);
    last = sorted_by_size.begin() + num_bags * 20 / 100; // 20%
    vector<node> top20(first, last);
    last = sorted_by_size.begin() + num_bags * 25 / 100; // 25%
    vector<node> top25(first, last);

    int index = 0;
    unordered_set<int> top_bags;
    vector<double> cnta1, cnta5, cnta10, cnta15, cnta20, cnta25;
    for (int per = 1; per <= SAMPLE; ++per) {
        for (; index < t.num_bags() * per / SAMPLE; ++index)
            top_bags.insert(bcs[index].second);
        while (bcs[index].first == bcs[index + 1].first) {
            if (bcs[index].first <= 0)
                break;
            top_bags.insert(bcs[index].second);
            ++index;
            if (index > t.num_bags() * (per + 1) / SAMPLE)
                ++per;
        }

        int cnt1 = 0;
        for (auto bag : top1)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt1++;
        int cnt5 = 0;
        for (auto bag : top5)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt5++;
        int cnt10 = 0;
        for (auto bag : top10)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt10++;
        int cnt15 = 0;
        for (auto bag : top15)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt15++;
        int cnt20 = 0;
        for (auto bag : top20)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt20++;
        int cnt25 = 0;
        for (auto bag : top25)
            if (top_bags.find(bag.node_id) != top_bags.end())
                cnt25++;

        if (bcs[index].first <= 0) {
            cnt1 = top1.size();
            cnt5 = top5.size();
            cnt10 = top10.size();
            cnt15 = top15.size();
            cnt20 = top20.size();
            cnt25 = top25.size();
        }
        cnta1.push_back((double)cnt1 / top1.size() * 100);
        cnta5.push_back((double)cnt5 / top5.size() * 100);
        cnta10.push_back((double)cnt10 / top10.size() * 100);
        cnta15.push_back((double)cnt15 / top15.size() * 100);
        cnta20.push_back((double)cnt20 / top20.size() * 100);
        cnta25.push_back((double)cnt25 / top25.size() * 100);
        output << (double)per / SAMPLE * 100 << " " << (double)cnt1 / top1.size() * 100 << " " << (double)cnt5 / top5.size() * 100 << " " << (double)cnt10 / top10.size() * 100 << " " << (double)cnt15 / top15.size() * 100 << " " << (double)cnt20 / top20.size() * 100 << " " << (double)cnt25 / top25.size() * 100 << " " << endl;
        if (bcs[index].first <= 0)
            break;
    }

    return 0;
}