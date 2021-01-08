#include "../communities.hpp"
#include "../tree_decomposition.hpp"
#include "../util.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    // Graph g;
    // string path_to_graph = "graph/" + filename + ".gr";
    // g.read_graph(path_to_graph);

    Tree_Decomposition t;
    string path_to_t = "tree/" + width + "-" + filename + ".tree";
    t.read_tree(path_to_t);

    Communities c;
    string path_to_c = "graph/community/" + filename + ".cm";
    c.read_community(path_to_c);

    vector<vector<int>> communities_in_tree;
    for (vector<int> community : c.get_communities()) {
        bool is_in_tree = true;
        for (int nd : community) {
            if (!t.exists(nd))
                is_in_tree = false;
        }
        if (is_in_tree)
            communities_in_tree.push_back(community);
    }
    // cout << "community: ";
    // int yeah = 81;
    // print_vector(communities_in_tree[yeah]);
    // cout << "path from root: " << endl;
    // for (int nd : communities_in_tree[yeah]) {
    //     print_vector(t.path_from_root(nd));
    // }

    string output_name = "output/community/" + width + "-" + filename + ".output";
    ofstream output(output_name);

    for (vector<int> comm : communities_in_tree) {
        int subtree_size = t.nodes_in_subtree(comm).size();
        int community_size = comm.size();
        int d = subtree_size - community_size;
        output << community_size << " " << subtree_size << " " << endl;
        cout << community_size << " " << subtree_size << " " << endl;
    }

    return 0;
}