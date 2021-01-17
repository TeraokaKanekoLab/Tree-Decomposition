#include "../betweenness_centrality.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

#define TOP_PERCENTAGE 10
#define SAMPLE 2000

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

    vector<pair<int, int>> by_size;
    vector<pair<int, int>> by_dist;
    vector<pair<int, int>> by_degree;
    vector<pair<int, int>> by_size_degree;
    for (int bag : t.all_bags()) {
        by_size.push_back(make_pair(t.subtree_size_induced_by(bag), bag));
        by_dist.push_back(make_pair(t.dist_from_leaf(bag), bag));
        by_degree.push_back(make_pair(g.degree(bag), bag));
        by_size_degree.push_back(make_pair(2 * t.subtree_size_induced_by(bag) - g.degree(bag), bag));
    }
    int num_bags = t.num_bags();
    int array_size = t.get_array_size();

    sort(by_size.begin(), by_size.end(), greater<pair<int, int>>());
    // by_size.resize(range);
    sort(by_dist.begin(), by_dist.end(), greater<pair<int, int>>());
    // by_dist.resize(range);
    sort(by_degree.begin(), by_degree.end(), greater<pair<int, int>>());
    // by_degree.resize(range);
    sort(by_size_degree.begin(), by_size_degree.end(), greater<pair<int, int>>());
    // by_size_degree.resize(range);

    cout << "root: " << t.get_root() << endl;
    cout << "size: " << by_size.size() << endl;
    vector<int> size_rank(array_size, 0);
    vector<int> dist_rank(array_size, 0);
    vector<int> degree_rank(array_size, 0);
    vector<int> size_degree_rank(array_size, 0);

    for (int i = 0; i < bcs.size(); ++i) {
        int nd = bcs[i].second;
        size_rank[nd] = i + 1;
        dist_rank[nd] = i + 1;
        degree_rank[nd] = i + 1;
        size_degree_rank[nd] = i + 1;
    }
    unordered_set<int> top_b;
    vector<int> sr, dir, der, sdr;
    int range = num_bags * 1 / SAMPLE;
    for (int index = 0; index < num_bags; index += range) {
        int diffsr = 0, diffdir = 0, diffder = 0, diffsdr = 0;
        int misssr = 0, missdir = 0, missder = 0, misssdr = 0;
        for (int i = 0; i < index + range; ++i) {
            top_b.insert(bcs[i].second);

            int r = size_rank[by_size[i].second];
            sr.push_back(r);
            diffsr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_size[i].second) != top_b.end())
                misssr++;

            r = dist_rank[by_dist[i].second];
            dir.push_back(r);
            diffdir += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_dist[i].second) != top_b.end())
                missdir++;

            r = degree_rank[by_degree[i].second];
            der.push_back(r);
            diffder += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_degree[i].second) != top_b.end())
                missder++;

            r = size_degree_rank[by_size_degree[i].second];
            sdr.push_back(r);
            diffsdr += (r - i - 1) * (r - i - 1);
            if (top_b.find(by_size_degree[i].second) != top_b.end())
                misssdr++;
        }

        // cout << diffsr << " " << (double)misssr / top_b.size() * 100 << "%" << endl;
        // cout << diffdir << " " << (double)missdir / top_b.size() * 100 << "%" << endl;
        // cout << diffder << " " << (double)missder / top_b.size() * 100 << "%" << endl;
        // cout << diffsdr << " " << (double)misssdr / top_b.size() * 100 << "%" << endl;

        output << (double)(index + range) / num_bags * 100
               << " " << (double)misssr / top_b.size() * 100
               << " " << (double)missdir / top_b.size() * 100
               << " " << (double)missder / top_b.size() * 100
               << " " << (double)misssdr / top_b.size() * 100 << endl;
    }

    return 0;
}