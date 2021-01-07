#include "../communities.hpp"
#include "../graph.hpp"
#include "../tree_decomposition.hpp"

int main(int argc, char* argv[])
{
    string filename = argv[1];
    string width = argv[2];

    // Graph g;
    // string path_to_graph = "graph/" + filename + ".gr";
    // g.read_edges(path_to_graph);

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
    int num_communities_in_tree = communities_in_tree.size();

    
    return 0;
}