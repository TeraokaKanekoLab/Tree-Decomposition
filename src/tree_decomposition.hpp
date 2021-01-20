#include "header.hpp"

class Tree_Decomposition {
    vector<vector<int>> nodes_in_bags;
    vector<int> parents;
    vector<vector<int>> children;
    unordered_set<int> bags;
    unordered_set<int> leaves;
    unordered_set<int> mainstream;
    int array_size;
    int root;
    vector<int> children_of_core;
    vector<int> eccentricities;
    vector<int> dist_from_parent;
    vector<int> dist_from_child;
    vector<int> dist_from_root;
    vector<int> widths;
    vector<int> subtree_sizes;
    vector<int> num_bags_including;
    vector<vector<int>> bags_including;
    vector<int> latest_remove_order_of;
    vector<int> latest_remove_order;
    vector<int> strahler;

    int compute_eccentricity_from_child(int nd)
    {
        int max = 0;
        if (dist_from_child[nd])
            return dist_from_child[nd];
        if (num_children(nd) == 0)
            return 0;
        for (int child : children[nd]) {
            int ec = compute_eccentricity_from_child(child);
            if (ec > max)
                max = ec;
        }
        dist_from_child[nd] = max + 1;
        return max + 1;
    }

    void compute_eccentricity_from_parent(int nd)
    {
        int parent = parent_of(nd);
        if (parent < 0)
            dist_from_parent[nd] = 0;
        else {
            int max = dist_from_parent[parent];
            for (int child : children_of(parent)) {
                if (child == nd)
                    continue;
                if (dist_from_child[child] + 1 > max)
                    max = dist_from_child[child] + 1;
            }
            dist_from_parent[nd] = max + 1;
        }
        for (int child : children_of(nd)) {
            compute_eccentricity_from_parent(child);
        }
    }

    void compute_eccentricities()
    {
        eccentricities = vector<int>(array_size, 0);
        dist_from_parent = vector<int>(array_size, 0);
        dist_from_child = vector<int>(array_size, 0);
        if (root < 0)
            for (int nd : children_of_core) {
                compute_eccentricity_from_child(nd);
                compute_eccentricity_from_parent(nd);
            }
        else {
            compute_eccentricity_from_child(root);
            compute_eccentricity_from_parent(root);
        }
        for (int i = 0; i < array_size; ++i) {
            int c = dist_from_child[i];
            int p = dist_from_parent[i];
            eccentricities[i] = max(c, p);
        }
    }

public:
    bool has_core;

    int num_bags()
    {
        return bags.size();
    }

    bool vector_is_small(int nd)
    {
        return nd > (int)parents.size() - 1;
    }

    void add_bag(int nd)
    {
        if (vector_is_small(nd)) {
            array_size = nd + 1;
            nodes_in_bags.resize(array_size, vector<int>());
            parents.resize(array_size);
            children.resize(array_size, vector<int>());
            latest_remove_order_of.resize(array_size);
        }
        latest_remove_order.push_back(nd);
        latest_remove_order_of[nd] = latest_remove_order.size();
        bags.insert(nd);
    }

    int get_root()
    {
        return root;
    }

    int get_array_size()
    {
        return array_size;
    }

    int get_remove_order_of(int nd)
    {
        if (!exists(nd))
            return -1;
        return num_bags() - latest_remove_order_of[nd] + 1;
    }

    int get_node_removed_at(int number)
    {
        // 1 origin
        if (number < 1 || number > array_size - 1)
            return -1;
        return latest_remove_order[num_bags() - number];
    }

    void read_tree(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << path << ": tree file not found" << endl;
            exit(-1);
        }

        string line;
        getline(file, line);
        if (line == "core") {
            has_core = true;
            root = -1;
            getline(file, line);
            getline(file, line);
        } else {
            has_core = false;
            int nd = stoi(line);
            root = nd;
            add_bag(nd);
            getline(file, line);
            getline(file, line);
            parents[nd] = -1;
            leaves.insert(nd);
        }

        while (getline(file, line)) {
            int nd = stoi(line);
            add_bag(nd);
            leaves.insert(nd);
            getline(file, line);
            int pos = 0;
            std::string delimiter = " ";
            while ((pos = line.find(delimiter)) != std::string::npos) {
                int node_in_bag = stoi(line.substr(0, pos));
                nodes_in_bags[nd].push_back(node_in_bag);
                line.erase(0, pos + delimiter.length());
            }
            if (!line.empty()) {
                int node_in_bag = stoi(line);
                nodes_in_bags[nd].push_back(node_in_bag);
            }
            getline(file, line);
            int parent = stoi(line);
            // child of core
            if (bags.find(parent) == bags.end()) {
                parents[nd] = -1;
                children_of_core.push_back(nd);
            } else {
                parents[nd] = parent;
                children[parent].push_back(nd);
                if (leaves.find(parent) != leaves.end())
                    leaves.erase(parent);
            }
        }
    }

    bool exists(int nd)
    {
        return !(bags.find(nd) == bags.end());
    }

    vector<int> children_of(int nd)
    {
        // cout << "size of children[" << nd << "] == " << children[nd].size() << endl;
        if (exists(nd))
            return children[nd];
        return vector<int>();
    }

    vector<int> get_nodes_in_bag(int nd)
    {
        if (!exists(nd))
            return vector<int>();
        return nodes_in_bags[nd];
    }

    int bagsize_of(int nd)
    {
        if (!exists(nd))
            return -1;
        return nodes_in_bags[nd].size() + 1;
    }

    int total_subtree_size_induced_by(int nd)
    {
        int size = 0;
        for (int bag : compute_bags_including(nd)) {
            size += nodes_in_bags[bag].size();
        }

        return size;
    }

    int subtree_size_induced_by(int nd)
    {
        if (!exists(nd))
            return 0;
        if (num_bags_including.size() < array_size) {
            num_bags_including.resize(array_size, 0);
            for (int bag : bags) {
                num_bags_including[bag] = 1;
            }
            for (auto nodes_in_bag : nodes_in_bags)
                for (int node : nodes_in_bag)
                    num_bags_including[node]++;
        }

        return num_bags_including[nd];
    }

    vector<int> compute_bags_including(int nd)
    {
        if (!exists(nd))
            return vector<int>();
        if (bags_including.size() < array_size) {
            bags_including.resize(array_size, vector<int>());
            for (int bag : bags)
                bags_including[bag].push_back(nd);

            // for (auto nodes_in_bag : nodes_in_bags)
            for (int i = 0; i < nodes_in_bags.size(); ++i) {
                vector<int> nodes_in_bag = nodes_in_bags[i];
                for (int node : nodes_in_bag)
                    bags_including[node].push_back(i);
            }
        }

        return bags_including[nd];
    }

    int num_whisk(int nd)
    {
        if (!exists(nd))
            return -1;
        int sum = 0;
        for (int child : children_of(nd))
            if (num_children(child) == 0)
                sum++;
        return sum;
    }

    int compute_width(int nd)
    {
        if (!exists(nd))
            return -1;
        if (widths.size() == 0)
            widths.resize(array_size, 0);
        if (widths[nd])
            return widths[nd];
        int width = bagsize_of(nd) - 1;
        for (int child : children[nd]) {
            int child_width = compute_width(child);
            if (child_width > width)
                width = child_width;
        }

        widths[nd] = width;
        return width;
    }

    vector<int> get_eccentricities()
    {
        if (eccentricities.size() != array_size)
            compute_eccentricities();
        return eccentricities;
    }

    int parent_of(int nd)
    {
        if (exists(nd))
            return parents[nd];
        return -1;
    }

    void print_tree()
    {
        for (auto bag : bags) {
            cout << bag << endl;
            auto nodes_in_bag = nodes_in_bags[bag];
            for (int node_in_bag : nodes_in_bag) {
                cout << node_in_bag << " ";
            }
            cout << endl;
            cout << parents[bag] << endl;
        }
    }

    void print_children_of(int nd)
    {
        cout << "children[nd].size() == " << children[nd].size() << endl;
        cout << "children of " << nd << ":";
        for (int child : children[nd])
            cout << " " << child;
        cout << endl;
    }

    int num_children(int nd)
    {
        if (!exists(nd))
            return -1;
        return children[nd].size();
    }

    int num_children_of_core()
    {
        if (!has_core)
            return 0;
        int num_children_of_core = 0;
        for (int bag : bags)
            if (parent_of(bag) < 0)
                num_children_of_core++;

        return num_children_of_core;
    }

    vector<int> all_bags()
    {
        vector<int> bags_vector;
        for (int bag : bags) {
            bags_vector.push_back(bag);
        }
        sort(bags_vector.begin(), bags_vector.end());

        return bags_vector;
    }

    double average_dist_in_group(vector<int> community)
    {
        int size = community.size();
        if (size < 2)
            return -1;
        int total_dist = 0;
        int num_pairs = size * (size - 1) / 2;
        for (int i = 0; i < size - 1; ++i) {
            int nd1 = community[i];
            for (int j = i + 1; j < size; ++j) {
                int nd2 = community[j];
                int d = dist(nd1, nd2);
                if (d < 0)
                    return -1;
                total_dist += d;
            }
        }

        return (double)total_dist / num_pairs;
    }

    int dist(int s, int t)
    {
        if (!exists(s) || !exists(t))
            return -1;
        vector<int> path1 = path_from_root(s);
        vector<int> path2 = path_from_root(t);
        int min_depth = min(path1.size(), path2.size());
        int common_depth = 0;
        while (common_depth < min_depth) {
            if (path1[common_depth] != path2[common_depth])
                break;
            common_depth++;
        }

        return path1.size() + path2.size() - 2 * common_depth;
    }

    int dist_from_leaf(int nd)
    {
        if (dist_from_child.size() != array_size) {
            dist_from_child.resize(array_size, 0);
            if (root < 0)
                for (int nd : children_of_core)
                    compute_eccentricity_from_child(nd);
            else
                compute_eccentricity_from_child(root);
        }
        return dist_from_child[nd];
    }

    int compute_dist_from_root(int nd)
    {
        if (dist_from_root.size() == 0)
            dist_from_root.resize(array_size, 0);
        if (dist_from_root[nd])
            return dist_from_root[nd];
        if (nd == root)
            return 0;
        int parent = parent_of(nd);
        int d = compute_dist_from_root(parent) + 1;
        dist_from_root[nd] = d;
        return d;
    }

    bool is_in_mainstream(int nd)
    {
        if (mainstream.size() != 0)
            return mainstream.find(nd) != mainstream.end();

        int max = 0;
        for (int bag : bags) {
            int d = compute_dist_from_root(bag);
            if (max < d)
                max = d;
        }
        for (int bag : bags) {
            int d = compute_dist_from_root(bag);
            if (d == max)
                for (int b : path_from_root(bag))
                    mainstream.insert(b);
        }
        cout << "#nodes = " << mainstream.size() << "(" << (double)mainstream.size() / num_bags() * 100 << "%)" << endl;

        return mainstream.find(nd) != mainstream.end();
    }

    vector<int> path_from_root(int nd)
    {
        vector<int> path;
        if (!exists(nd))
            return vector<int>();
        path.push_back(nd);
        while ((nd = parents[nd]) >= 0) {
            path.push_back(nd);
        }
        if (has_core)
            path.push_back(-1);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> nodes_in_subtree(vector<int> nds)
    {
        vector<int> nodes_in_subtree;
        vector<vector<int>> paths_from_root;
        unordered_set<int> nodes_in_subtree_set;

        int max_path_length = path_from_root(nds[0]).size();
        int min_path_length = max_path_length;
        int min_nd = nds[0];
        for (int nd : nds) {
            vector<int> path = path_from_root(nd);
            for (int nd_in_path : path)
                nodes_in_subtree_set.insert(nd_in_path);
            paths_from_root.push_back(path);
            if (max_path_length < path.size())
                max_path_length = path.size();
            if (min_path_length > path.size()) {
                min_path_length = path.size();
                min_nd = nd;
            }
        }

        int prev = paths_from_root[0][0];
        for (int i = 0; i < max_path_length; ++i) {
            int def = paths_from_root[0][i];
            bool all_same = true;
            for (vector<int> path : paths_from_root) {
                if (path[i] != def) {
                    all_same = false;
                    break;
                }
            }
            if (def == min_nd && all_same)
                break;

            if (all_same) {
                nodes_in_subtree_set.erase(def);
                prev = def;
            } else {
                nodes_in_subtree_set.insert(prev);
                break;
            }
        }
        for (int nd : nodes_in_subtree_set) {
            nodes_in_subtree.push_back(nd);
        }

        sort(nodes_in_subtree.begin(), nodes_in_subtree.end());

        return nodes_in_subtree;
    }

    int subtree_size(int nd)
    {
        if (subtree_sizes.size() != array_size)
            subtree_sizes.resize(array_size, 0);
        if (subtree_sizes[nd])
            return subtree_sizes[nd];
        int size = 1;
        for (int child : children_of(nd)) {
            size += subtree_size(child);
        }
        subtree_sizes[nd] = size;
        return size;
    }

    int compute_betweenness_centrality(int nd)
    {
        if (nd == root)
            return 0;
        if (leaves.find(nd) != leaves.end())
            return 0;
        vector<int> components;
        components.push_back(num_bags() - subtree_size(nd));
        for (int child : children_of(nd)) {
            components.push_back(subtree_size(child));
        }

        int paths = 0;
        for (int i = 0; i < components.size() - 1; ++i) {
            for (int j = i + 1; j < components.size(); ++j) {
                paths += components[i] * components[j];
            }
        }
        return paths;
    }

    int compute_strahler(int nd)
    {
        if (!exists(nd))
            return -1;
        if (strahler.size() == 0)
            strahler.resize(array_size, 0);
        if (strahler[nd])
            return strahler[nd];
        if (num_children(nd) == 0) {
            strahler[nd] = 1;
            return 1;
        }

        int max = 0;
        bool should_add_one = false;
        for (int child : children_of(nd)) {
            int child_strahler = compute_strahler(child);
            if (child_strahler > max) {
                max = child_strahler;
                should_add_one = false;
            } else if (child_strahler == max) {
                should_add_one = true;
            }
        }
        if (should_add_one) {
            strahler[nd] = max + 1;
            if (max == 7)
                cout << "branch at " << nd << endl;
            return max + 1;
        }
        strahler[nd] = max;
        return max;
    }

    int depth()
    {
        int max = 0;
        for (int nd : all_bags()) {
            int d = compute_dist_from_root(nd);
            if (d > max)
                max = d;
        }
        return max;
    }

    void export_info(string filepath)
    {
        ofstream file(filepath);
        for (int nd : all_bags()) {
            int nc = num_children(nd);
            int bs = bagsize_of(nd);
            int dl = dist_from_leaf(nd);
            int w = compute_width(nd);
            file << num_children(nd) << " " << bagsize_of(nd) << " " << dist_from_leaf(nd) << " " << compute_width(nd) << endl;
        }
        file.close();
    }
};