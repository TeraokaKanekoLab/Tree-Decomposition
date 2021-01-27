#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 2000

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
    string width = "1000000";

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

    string output_name = "output/select-topk/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    vector<node> by_iss;
    vector<node> by_dist;
    vector<node> by_degree;
    vector<node> by_sum_strahler;
    vector<node> by_child;
    for (int bg : t.all_bags()) {
        by_iss.push_back(node(bg, t.bagsize_of(bg), t.subtree_size_induced_by(bg), true));
        by_degree.push_back(node(bg, t.bagsize_of(bg), g.degree(bg), false));
        int sum = 0;
        for (int child : t.children_of(bg))
            sum += t.compute_strahler(child);
        by_sum_strahler.push_back(node(bg, t.bagsize_of(bg), sum, true));
        by_child.push_back(node(bg, t.bagsize_of(bg), t.num_children(bg), true));
        by_dist.push_back(node(bg, t.bagsize_of(bg), t.subtree_size_induced_by(bg) + sum, true));
    }
    int num_bags = t.num_bags();
    int array_size = t.get_array_size();

    sort(by_iss.begin(), by_iss.end(), sort_by_metric);
    // by_iss.resize(range);
    sort(by_dist.begin(), by_dist.end(), sort_by_metric);
    // by_dist.resize(range);
    sort(by_degree.begin(), by_degree.end(), sort_by_metric);
    // by_degree.resize(range);
    sort(by_sum_strahler.begin(), by_sum_strahler.end(), sort_by_metric);
    // by_sum_strahler.resize(range);
    sort(by_child.begin(), by_child.end(), sort_by_metric);
    // by_sum_strahler.resize(range);

    cout << "root: " << t.get_root() << endl;
    cout << "size: " << by_iss.size() << endl;
    vector<int> iss_rank(array_size, 0);
    vector<int> dist_rank(array_size, 0);
    vector<int> degree_rank(array_size, 0);
    vector<int> size_degree_rank(array_size, 0);
    vector<int> child_rank(array_size, 0);

    int cnt = 0;
    for (int i = 0; i < bcs.size(); ++i) {
        int nd = bcs[i].second;
        iss_rank[nd] = i + 1;
        dist_rank[nd] = i + 1;
        degree_rank[nd] = i + 1;
        size_degree_rank[nd] = i + 1;
        child_rank[nd] = i + 1;
    }
    unordered_set<int> top_b;
    vector<int> sr, dir, dgr, sdr, ch;
    int range = num_bags * 1 / SAMPLE;
    for (int index = 0; index < num_bags; index += range) {
        int diffsr = 0, diffdir = 0, diffdgr = 0, diffsdr = 0, diffch = 0;
        int hit_iss = 0, hit_dist = 0, hit_degree = 0, hit_sum_strahler = 0, hit_child = 0;
        bool has_reached_zero = false;
        for (int i = 0; i < index + range; ++i) {
            if (bcs[i].first <= 0)
                has_reached_zero = true;
            top_b.insert(bcs[i].second);

            int r = iss_rank[by_iss[i].node_id];
            sr.push_back(r);
            diffsr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_iss[i].node_id) != top_b.end())
                hit_iss++;

            r = dist_rank[by_dist[i].node_id];
            dir.push_back(r);
            diffdir += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_dist[i].node_id) != top_b.end())
                hit_dist++;

            r = degree_rank[by_degree[i].node_id];
            dgr.push_back(r);
            diffdgr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_degree[i].node_id) != top_b.end())
                hit_degree++;

            r = size_degree_rank[by_sum_strahler[i].node_id];
            sdr.push_back(r);
            diffsdr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_sum_strahler[i].node_id) != top_b.end())
                hit_sum_strahler++;

            r = child_rank[by_child[i].node_id];
            ch.push_back(r);
            diffch += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_child[i].node_id) != top_b.end())
                hit_child++;
        }

        output << (double)(index + range) / num_bags * 100
               << " " << (double)hit_iss / top_b.size() * 100
               << " " << (double)hit_dist / top_b.size() * 100
               << " " << (double)hit_child / top_b.size() * 100
               << " " << (double)hit_sum_strahler / top_b.size() * 100
               << " " << (double)hit_degree / top_b.size() * 100 << endl;

        if (has_reached_zero) {
            break;
        }
    }
    cout << "cnt = " << cnt << endl;

    return 0;
}