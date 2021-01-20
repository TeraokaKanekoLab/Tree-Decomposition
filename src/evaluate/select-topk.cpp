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

    vector<node> by_size;
    vector<node> by_dist;
    vector<node> by_degree;
    vector<node> by_size_degree;
    vector<node> by_child;
    for (int bg : t.all_bags()) {
        by_size.push_back(node(bg, t.bagsize_of(bg), t.subtree_size_induced_by(bg), true));
        // by_size.push_back(node(bg, t.bagsize_of(bg), 5 * t.subtree_size_induced_by(bg) + g.degree(bg), true));
        by_dist.push_back(node(bg, t.bagsize_of(bg), t.dist_from_leaf(bg), true));
        // by_dist.push_back(node(bg, t.bagsize_of(bg), 10 * t.subtree_size_induced_by(bg) + g.degree(bg), true));
        by_degree.push_back(node(bg, t.bagsize_of(bg), g.degree(bg), false));
        // by_degree.push_back(node(bg, t.bagsize_of(bg), 20 * t.subtree_size_induced_by(bg) + g.degree(bg), true));
        int sum = 0;
        for (int child : t.children_of(bg))
            sum += t.compute_strahler(child);
        by_size_degree.push_back(node(bg, t.bagsize_of(bg), sum, true));
        by_child.push_back(node(bg, t.bagsize_of(bg), t.num_children(bg), true));
    }
    int num_bags = t.num_bags();
    int array_size = t.get_array_size();

    sort(by_size.begin(), by_size.end(), sort_by_metric);
    // by_size.resize(range);
    sort(by_dist.begin(), by_dist.end(), sort_by_metric);
    // by_dist.resize(range);
    sort(by_degree.begin(), by_degree.end(), sort_by_metric);
    // by_degree.resize(range);
    sort(by_size_degree.begin(), by_size_degree.end(), sort_by_metric);
    // by_size_degree.resize(range);
    sort(by_child.begin(), by_child.end(), sort_by_metric);
    // by_size_degree.resize(range);

    cout << "root: " << t.get_root() << endl;
    cout << "size: " << by_size.size() << endl;
    vector<int> size_rank(array_size, 0);
    vector<int> dist_rank(array_size, 0);
    vector<int> degree_rank(array_size, 0);
    vector<int> size_degree_rank(array_size, 0);
    vector<int> child_rank(array_size, 0);

    int cnt = 0;
    for (int i = 0; i < bcs.size(); ++i) {
        int nd = bcs[i].second;
        size_rank[nd] = i + 1;
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
        int misssr = 0, missdir = 0, missdgr = 0, misssdr = 0, missch = 0;
        bool has_reached_zero = false;
        for (int i = 0; i < index + range; ++i) {
            if (bcs[i].first <= 0)
                has_reached_zero = true;
            top_b.insert(bcs[i].second);

            int r = size_rank[by_size[i].node_id];
            sr.push_back(r);
            diffsr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_size[i].node_id) != top_b.end())
                misssr++;

            r = dist_rank[by_dist[i].node_id];
            dir.push_back(r);
            diffdir += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_dist[i].node_id) != top_b.end())
                missdir++;

            r = degree_rank[by_degree[i].node_id];
            dgr.push_back(r);
            diffdgr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_degree[i].node_id) != top_b.end())
                missdgr++;

            r = size_degree_rank[by_size_degree[i].node_id];
            sdr.push_back(r);
            diffsdr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_size_degree[i].node_id) != top_b.end())
                misssdr++;

            r = child_rank[by_child[i].node_id];
            ch.push_back(r);
            diffch += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_child[i].node_id) != top_b.end())
                missch++;
        }

        output << (double)(index + range) / num_bags * 100
               << " " << (double)misssr / top_b.size() * 100
               << " " << (double)missch / top_b.size() * 100
               << " " << (double)misssdr / top_b.size() * 100
               << " " << (double)missdgr / top_b.size() * 100 << endl;

        if (has_reached_zero) {
            break;
        }
    }
    cout << "cnt = " << cnt << endl;

    return 0;
}