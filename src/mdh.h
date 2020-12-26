#include "graph.h"

#define TRIALS 10

class mdh : public Graph {
public:
    unordered_map<int, unordered_set<int>> neighbors_of;
    int init_degree;

    void make_graph()
    {
        for (pair<int, int> e : edges) {
            neighbors_of[e.first].insert(e.second);
            neighbors_of[e.second].insert(e.first);
        }
    }

    void clique(vector<int>& nbrs)
    {
        for (int nbr1 : nbrs) {
            for (int nbr2 : nbrs) {
                if (nbr1 == nbr2)
                    continue;
                if (neighbors_of[nbr1].find(nbr2) == neighbors_of[nbr1].end())
                    neighbors_of[nbr1].insert(nbr2);
            }
        }
    }

    vector<int> create_index_array(int num_elems)
    {
        vector<int> degs(num_nodes, 0);
        vector<node> node_array;
        vector<int> index_array;
        double param = 0.7;
        for (pair<int, int> e : edges) {
            degs[e.first]++;
            degs[e.second]++;
        }
        for (int i = 0; i < degs.size(); ++i)
            if (degs[i] > 0)
                node_array.push_back(node(degs[i], i));

        sort(node_array.begin(), node_array.end());
        int interval = 1;
        if (node_array.size() > num_elems)
            interval = node_array.size() / num_elems;
        for (int i = 0; i < node_array.size() - int(num_elems * param); i += interval) {
            index_array.push_back(node_array[i].second);
            // cout << "width: " << node_array[i].first << endl;
        }
        // high-degree nodes
        for (int i = node_array.size() - int(num_elems * param); i < node_array.size(); ++i) {
            index_array.push_back(node_array[i].second);
            // cout << "width: " << node_array[i].first << endl;
        }
        return index_array;
    }

    void export_info_start(
        ofstream& output,
        int duration,
        int num_visited)
    {
        cout << "remove cnt: " << remove_cnt << ", depth: " << depth_of_tree << ", leaf: " << 100 * (double)leaf_cnt / remove_cnt << "%, child: " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << ", strahler: " << strahler_of_root << endl;
        output << init_degree << " " << remove_cnt << " " << double(duration) / 1000000 << " " << depth_of_tree << " " << (double)leaf_cnt / remove_cnt << " " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << " " << (double)remove_cnt / num_visited * 100 << " " << strahler_of_root << endl;
    }
};
