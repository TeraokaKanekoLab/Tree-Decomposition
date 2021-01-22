#include "header.hpp"

#define TRIALS 10

string filename;
vector<pair<int, int>> edges;

class mdh {
public:
    unordered_map<int, unordered_set<int>> neighbors_of;
    int init_degree;
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int true_num_nodes = 0;
    int remove_cnt = 0;
    deque<pair<int, vector<int>>> node_stack;
    typedef pair<int, int> node; // (deg, vertex)
    int max_tree_width = 0;
    vector<int> depth;
    vector<int> parents;
    vector<vector<int>> children;
    vector<int> children_of_core;
    vector<int> initial_degree;
    int root_node = -1;
    int depth_of_tree = 0;
    int leaf_cnt = 0;
    int total_child_cnt = 0;
    vector<int> strahler_nums;
    int strahler_of_root = 0;

public:
    void add_edge(int u, int v)
    {
        edges.push_back({ u, v });
    }

    void read_edges()
    {
        ifstream graph_data("graph/" + filename + ".gr");

        if (!graph_data.good()) {
            cout << "file not found" << endl;
            exit(-1);
        }

        // ignore commented out lines
        string tp;
        streampos oldpos = graph_data.tellg();
        while (getline(graph_data, tp)) {
            if (tp.find("#") == string::npos) {
                graph_data.seekg(oldpos);
                break;
            }
            oldpos = graph_data.tellg();
        }

        // start reading edge information from file
        int u, v;
        while (graph_data >> u >> v) {
            add_edge(u, v);
            // compute number of nodes (|V|) and number of edges (|E|)
            num_nodes = max(num_nodes, max(u, v) + 1);
        }
        graph_data.close();
    }
    void export_info(
        ofstream& output,
        int tree_width,
        int remove_cnt,
        int true_num_nodes,
        int duration,
        int num_visited)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)"
             << " " << double(duration) / 1000000 << endl;
        output << tree_width << " " << remove_cnt << " " << double(duration) / 1000000 << " " << depth_of_tree << " " << (double)leaf_cnt / remove_cnt << " " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << " " << (double)remove_cnt / num_visited * 100 << " " << strahler_of_root << endl;
    }

    void export_info_step(
        ofstream& output,
        int tree_width,
        int remove_cnt,
        int true_num_nodes,
        int duration,
        int num_visited)
    {
        cout << "remove cnt: " << remove_cnt << ", depth: " << depth_of_tree << ", leaf: " << 100 * (double)leaf_cnt / remove_cnt << "%, child: " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << ", strahler: " << strahler_of_root << endl;
        output << tree_width << " " << remove_cnt << " " << double(duration) / 1000000 << " " << depth_of_tree << " " << (double)leaf_cnt / remove_cnt << " " << (double)total_child_cnt / (remove_cnt - leaf_cnt) << " " << (double)remove_cnt / num_visited * 100 << " " << strahler_of_root << endl;
    }

    void make_tree()
    {
        // initialize
        depth.resize(num_nodes, 0);
        parents.resize(num_nodes, -1);
        children.clear();
        children.resize(num_nodes, vector<int>());
        children_of_core.clear();
        vector<int> child_cnt(num_nodes, 0);
        int num_core_child = 0;

        for (int i = 0; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            vector<int> nbrs = node_stack[i].second;
            int parent = -1; // the parent is itselft at first
            int max_depth = -1;
            sort(nbrs.begin(), nbrs.end());
            for (int nbr : nbrs)
                if (depth[nbr] > max_depth) {
                    max_depth = depth[nbr];
                    parent = nbr;
                }
            depth[nd] = max_depth + 1;
            if (max_depth == -1)
                num_core_child++;
            parents[nd] = parent;
            if (parent >= 0) {
                child_cnt[parent]++;
                children[parent].push_back(nd);
            } else if (parent < 0) {
                // then nd is a child of core
                children_of_core.push_back(nd);
            }
        }

        depth_of_tree = 0;
        leaf_cnt = 0;
        total_child_cnt = 0;
        for (int i = 0; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            if (depth[nd] > depth_of_tree)
                depth_of_tree = depth[nd];
            if (child_cnt[nd] == 0)
                leaf_cnt++;
            total_child_cnt += child_cnt[nd];
        }
        if (remove_cnt == true_num_nodes) {
            // no core
            root_node = node_stack[0].first;
        }
        compute_strahler();
    }

    void print_depth_bagsize()
    {
        string output_name = "output/depth-bagsize/" + to_string(max_tree_width) + "-" + filename + ".output";
        ofstream depth_bagize_output(output_name);
        for (int i = 0; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            vector<int> nbrs = node_stack[i].second;
            int bag_size = nbrs.size();
            int d = depth[nd];
            depth_bagize_output << d << " " << bag_size << endl;
        }
    }

    void print_stack()
    {
        string output_name = "tree/" + to_string(max_tree_width) + "-" + filename + ".tree";
        ofstream tree_output(output_name);
        int start = 0;
        // decide whether there is a core or not
        if (remove_cnt == true_num_nodes) {
            // print root node in the tree
            int root = node_stack[0].first;
            vector<int> root_nbrs = node_stack[0].second;
            tree_output << root << endl;
            sort(root_nbrs.begin(), root_nbrs.end());
            for (int nbr : root_nbrs)
                tree_output << nbr << " ";
            tree_output << endl;
            tree_output << "root" << endl;
            start = 1;
        } else {
            tree_output << "core" << endl;
            tree_output << endl;
            tree_output << "root" << endl;
        }

        for (int i = start; i < node_stack.size(); ++i) {
            int nd = node_stack[i].first;
            vector<int> nbrs = node_stack[i].second;

            // ouput <nd> <nbr 1> <nbr 2> ... <nbr n> <parent>
            tree_output << nd << endl;
            for (int nbr : nbrs) {
                tree_output << nbr << " ";
            }
            tree_output << endl;
            tree_output << parents[nd] << endl;
        }
    }

    void add_to_stack(int nd, vector<int> nbrs)
    {
        vector<int> new_nbrs;
        for (int nbr : nbrs)
            if (nbr != nd)
                new_nbrs.push_back(nbr);
        node_stack.push_front(make_pair(nd, new_nbrs));
    }

    void print_priority_queue(priority_queue<node, vector<node>, greater<node>> degreeq)
    {
        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            degreeq.pop();
            cout << "(" << nd << ", " << deg << ") ";
        }
        cout << endl;
    }

    void compute_strahler()
    {
        strahler_nums.resize(num_nodes, 1); // strahler number of leaf is 1
        if (root_node > 0) {
            strahler_of_root = strahler(root_node);
        } else {
            int max = 0;
            bool should_add_one = false;

            for (int child : children_of_core) {
                int child_strahler = strahler(child);
                if (child_strahler > max) {
                    max = child_strahler;
                    should_add_one = false;
                } else if (child_strahler == max) {
                    should_add_one = true;
                }
            }
            if (should_add_one)
                strahler_of_root = max + 1;
            else if (max == 0)
                strahler_of_root = 1;
            else
                strahler_of_root = max;
        }
        // cout << "strahler of root: " << strahler_of_root << endl;
    }

    int strahler(int nd)
    {
        int max = 0;
        bool should_add_one = false;

        for (int child : children[nd]) {
            int child_strahler = strahler(child);
            if (child_strahler > max) {
                max = child_strahler;
                should_add_one = false;
            } else if (child_strahler == max) {
                should_add_one = true;
            }
        }
        if (should_add_one)
            return max + 1;
        else if (max == 0)
            return 1;
        else
            return max;
    }

    void make_graph()
    {
        for (pair<int, int> e : edges) {
            if (e.first == e.second)
                continue;
            neighbors_of[e.first].insert(e.second);
            neighbors_of[e.second].insert(e.first);
        }
    }

    void clique(int nd, vector<int>& nbrs, ofstream& output)
    {
        // for (int nbr1 : nbrs) {
        //     for (int nbr2 : nbrs) {
        //         if (nbr1 == nbr2)
        //             continue;
        //         if (neighbors_of[nbr1].find(nbr2) == neighbors_of[nbr1].end())
        //             neighbors_of[nbr1].insert(nbr2);
        //     }
        // }
        int size = nbrs.size();
        int hit = 0;
        for (int i = 0; i < size - 1; ++i) {
            int nbr1 = nbrs[i];
            for (int j = i + 1; j < size; ++j) {
                int nbr2 = nbrs[j];
                if (neighbors_of[nbr1].find(nbr2) == neighbors_of[nbr1].end()) {
                    neighbors_of[nbr1].insert(nbr2);
                    neighbors_of[nbr2].insert(nbr1);
                    hit++;
                }
            }
        }
        if (size > 1)
            output << nd << " " << hit << " " << size << endl;
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
