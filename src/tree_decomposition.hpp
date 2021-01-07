#include "header.hpp"

class Tree_Decomposition {
    vector<vector<int>> nodes_in_bags;
    vector<int> parents;
    vector<vector<int>> children;
    unordered_map<int, bool> bags;

public:
    bool has_core;

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
        bags[nd] = true;
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
            cout << bag.first << endl;
            auto nodes_in_bag = nodes_in_bags[bag.first];
            for (int node_in_bag : nodes_in_bag) {
                cout << node_in_bag << " ";
            }
            cout << endl;
            cout << parents[bag.first] << endl;
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

    vector<int> path_from_root(int nd)
    {
        vector<int> path(nd);
        while (nd = parents[nd] < 0) {
            path.push_back(nd);
        }
        if (has_core)
            path.push_back(-1);
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> nodes_in_subtree(vector<int> nds)
    {
    }
};