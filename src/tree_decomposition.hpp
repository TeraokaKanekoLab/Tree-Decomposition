#include "header.hpp"

class Tree_Decomposition {
    vector<vector<int>> nodes_in_bags;
    vector<int> parents;
    vector<vector<int>> children;
    unordered_set<int> bags;

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
            nodes_in_bags.resize(nd + 1, vector<int>());
            parents.resize(nd + 1);
            children.resize(nd + 1, vector<int>());
        }
        bags.insert(nd);
    }

    void read_tree(string path)
    {
        ifstream file(path);

        if (!file.good()) {
            cout << "tree file not found" << endl;
            exit(-1);
        }

        string line;
        streampos oldpos = file.tellg();
        getline(file, line);
        if (line == "core") {
            has_core = true;
            getline(file, line);
            getline(file, line);
        } else {
            has_core = false;
            file.seekg(oldpos);
        }

        while (getline(file, line)) {
            int nd = stoi(line);
            add_bag(nd);
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
            if (bags.find(parent) == bags.end())
                parents[nd] = -1;
            else {
                parents[nd] = parent;
                children[parent].push_back(nd);
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

    vector<int> path_from_root(int nd)
    {
        vector<int> path;
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
};