#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define MAX_TREE_WIDTH 100

using namespace std;

struct graph {
    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0; // This value may be different from the official number of nodes.
    int num_edges = 0;
    vector<pair<int, int>> edges;
    string filename;
    string path;
    unordered_map<int, unordered_set<int>> neighbors_of;

    void add_edge(int u, int v)
    {
        edges.push_back({ u, v });
    }

    void make_graph()
    {
        for (pair<int, int> e : edges) {
            neighbors_of[e.first].insert(e.second);
            neighbors_of[e.second].insert(e.first);
        }
    }

    void read_edges(string file_name)
    {
        ifstream graph_data(file_name);
        int idx = file_name.find("graph/");
        filename = file_name.substr(idx + 6);
        path = file_name.substr(0, idx);

        if (!graph_data.good()) {
            cout << filename << ": file not found" << endl;
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
            num_edges++;
        }
        graph_data.close();
    }

    void decompose(int max_tree_width)
    {
        typedef pair<int, int> node; // (deg, vertex)
        ofstream output(path + "output/" + to_string(max_tree_width) + "-mdh-" + filename);
        int true_num_nodes = 0;
        int crnt_deg = 1;
        int remove_cnt = 0;
        priority_queue<node, vector<node>, greater<node>> degreeq;

        // counts vertices with edges (exclude non-edged vertex)
        // initialize priority queue
        for (int i = 0; i < neighbors_of.size(); ++i) {
            int deg = neighbors_of[i].size();
            if (deg) {
                true_num_nodes++;
                degreeq.push(node(deg, i));
            }
        }
        auto start = std::chrono::steady_clock::now();
        auto end = std::chrono::steady_clock::now();
        auto d2_start = std::chrono::steady_clock::now();
        auto d2_end = std::chrono::steady_clock::now();
        auto d2_duration = chrono::duration_cast<chrono::microseconds>(chrono::milliseconds(0));
        auto n_start = std::chrono::steady_clock::now();
        auto n_end = std::chrono::steady_clock::now();
        auto n_duration = chrono::duration_cast<chrono::microseconds>(chrono::milliseconds(0));
        while (!degreeq.empty()) {
            int deg = degreeq.top().first;
            int nd = degreeq.top().second;
            degreeq.pop();
            if (neighbors_of.find(nd) == neighbors_of.end() || deg != neighbors_of[nd].size())
                continue; // outdated entry in degreeq
            if (deg > crnt_deg) {
                end = std::chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                export_info(crnt_deg, remove_cnt, true_num_nodes, output, duration, n_duration, d2_duration);
                crnt_deg = deg;
                n_duration = chrono::duration_cast<chrono::microseconds>(chrono::milliseconds(0));
                d2_duration = chrono::duration_cast<chrono::microseconds>(chrono::milliseconds(0));
                start = std::chrono::steady_clock::now();
            }
            if (deg > max_tree_width)
                break;
            vector<int> nbrs;
            for (int nbr : neighbors_of[nd])
                nbrs.push_back(nbr);
            auto d2_start = std::chrono::steady_clock::now();
            for (int nbr1 : nbrs) {
                for (int nbr2 : nbrs) {
                    if (nbr1 == nbr2)
                        continue;
                    if (neighbors_of[nbr1].find(nbr2) == neighbors_of[nbr1].end())
                        neighbors_of[nbr1].insert(nbr2);
                }
            }
            auto d2_end = std::chrono::steady_clock::now();
            d2_duration += chrono::duration_cast<chrono::microseconds>(d2_end - d2_start);
            auto n_start = std::chrono::steady_clock::now();
            for (int nbr : nbrs) {
                neighbors_of[nbr].erase(nd);
                degreeq.push(node(neighbors_of[nbr].size(), nbr));
            }
            auto n_end = std::chrono::steady_clock::now();
            n_duration += chrono::duration_cast<chrono::microseconds>(n_end - n_start);
            neighbors_of.erase(nd);
            remove_cnt++;
        }
        output.close();
    }
    void export_info(int tree_width, int remove_cnt, int true_num_nodes, ofstream& output, chrono::microseconds duration, chrono::microseconds n_duration, chrono::microseconds d2_duration)
    {
        cout << "width: " << tree_width << ", removed: " << remove_cnt << " (" << (double)remove_cnt / true_num_nodes * 100 << "%)"
             << " " << double(duration.count()) / 1000000 << ", n: " << double(n_duration.count()) / 1000000 << ", d2: " << double(d2_duration.count()) / 1000000 << endl;
        output << tree_width << " " << remove_cnt << " " << double(duration.count()) / 1000000 << endl;
    }

    void
    print_neighbor(int u, vector<int> nbh)
    {
        cout << u << ": [";
        for (int i = 0; i < nbh.size(); ++i) {
            if (i == nbh.size() - 1)
                cout << nbh[i];
            else
                cout << nbh[i] << ", ";
        }
        cout << "]" << endl;
    }
};

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <filename> <tree width>" << endl;
        exit(-1);
    }

    graph g;
    g.read_edges(argv[1]);
    g.make_graph();

    g.decompose(stoi(argv[2]));

    return 0;
}
