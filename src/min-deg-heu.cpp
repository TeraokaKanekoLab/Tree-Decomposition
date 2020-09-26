/*
min-deg-heu.cpp

Created by Cirus Thenter on 2020/08/27.
Copyright © 2020 Cirus Thenter. All rights reserved?

# how to run this program
% g++ min-deg-heu.cpp -o min-deg-heu
% ./min-deg-heu <graph data file>


# gaph data format
<# of nodes> <# of edges>
<endpoint 1> <endpoint 2>
<endpoint 3> <endpoint 4>
.
.
.

<endpoint n> needs to be int (edge No.)
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define TREE_WIDTH 2

struct node {
    int degree;
    int number;
    int key_degree;
    bool is_hub; // true if the node's type is hub and false if it is normal; default of is_hub: false
    std::vector<int> endpoints;
};

// We are doing operator overloading through this
// if node A's degree is smaller than node B's, we consider node A "bigger" than node B
// this funciton is for sorting all nodes in increasing order of degree.
// if n1 and n2 have the same degree, node with smaller number is "bigger"
bool operator<(const node& n1, const node& n2)
{
    if (n1.key_degree != n2.key_degree)
        return n1.key_degree > n2.key_degree;
    else
        return n1.number > n2.number;
}

void print_adj_matrix(int num_nodes, const std::vector<std::vector<bool>>& adj_matrix)
{
    std::cout << "  ";
    for (int i = 0; i < num_nodes; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < num_nodes; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < num_nodes; ++j) {
            if (adj_matrix[i][j])
                std::cout << "1 ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

void read_graph_data(
    int& num_nodes,
    int& num_edges,
    std::vector<std::vector<bool>>& adj_matrix,
    std::vector<node>& nodes,
    std::string filename)
{
    std::ifstream graph_data(filename);
    if (!graph_data.good()) {
        std::cout << filename << ": file not found" << std::endl;
        exit(-1);
    }

    // read the size of the graph (# of nodes and # of edges)
    graph_data >> num_nodes >> num_edges;

    // create adjancy matrix
    for (int i = 0; i < num_nodes; ++i) {
        std::vector<bool> there_edge;
        for (int i = 0; i < num_nodes; ++i) {
            there_edge.push_back(false);
        }
        adj_matrix.push_back(there_edge);
    }

    // initialize all nodes
    for (int i = 0; i < num_nodes; ++i) {
        node new_node;
        new_node.degree = 0;
        new_node.number = i;
        new_node.is_hub = false;
        nodes.push_back(new_node);
    }

    // save edge information to each node
    for (int i = 0; i < num_edges; ++i) {
        int ep1, ep2;
        graph_data >> ep1 >> ep2;
        nodes[ep1].degree++;
        nodes[ep1].key_degree++;
        nodes[ep1].endpoints.push_back(ep2);
        nodes[ep2].key_degree++;
        nodes[ep2].endpoints.push_back(ep1);
        adj_matrix[ep1][ep2] = true;
        adj_matrix[ep2][ep1] = true;
    }

    graph_data.close();
}

void create_priority_queue(
    const int num_nodes,
    const std::vector<node>& nodes,
    std::priority_queue<node>& nodes_to_remove)
{
    for (int i = 0; i < num_nodes; ++i) {
        nodes_to_remove.push(nodes[i]);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return -1;
    }

    // We expect the number of nodes and that of edges are both under INT_MAX = 2,147,483,647
    // on the assumption that the biggest number in https://snap.stanford.edu/data/ is 1,806,067,135 of com-Friendster.
    // We consider int type suitable for this situation.
    int num_nodes = 0;
    int num_edges = 0;
    std::vector<std::vector<bool>> adj_matrix;
    std::vector<node> nodes;
    read_graph_data(num_nodes, num_edges, adj_matrix, nodes, argv[1]);

    std::priority_queue<node> nodes_to_remove;
    create_priority_queue(num_nodes, nodes, nodes_to_remove);

    while (true) {
        node rm_node = nodes_to_remove.top();
        // compute current degree (true degree)
        rm_node.degree = 0;
        std::set<int> neighbors;
        for (int neighbor_int : rm_node.endpoints) {
            node neighbor = nodes[neighbor_int];
            if (neighbor.is_hub) {
                for (int hub_neighbor : neighbor.endpoints)
                    neighbors.insert(hub_neighbor); // A hub's neighbor is not a hub; always normal
            } else {
                neighbors.insert(neighbor_int);
            }
        }
        neighbors.erase(rm_node.number);
        rm_node.degree = neighbors.size(); // true degree is the size of the set of its neighbors
        if (rm_node.degree > TREE_WIDTH)
            break;
        nodes_to_remove.pop();
        if (rm_node.key_degree != rm_node.degree) {
            rm_node.key_degree = rm_node.degree;
            nodes_to_remove.push(rm_node); // reinsert if the key degree is different from the true key
            continue;
        }
        // We are in a "general situation" described in the paper p. 1029 left bottom.
        // We would like to see all the neighbors that are hubs.
        rm_node.is_hub = true;
        for (int neighbor_int : rm_node.endpoints) {
            node neighbor = nodes[neighbor_int]; // neighbor: one of the neighbors of rm_node
            if (!neighbor.is_hub)
                continue;
            // If we are here, neighbor is a hub
            for (int hub_neighbor : neighbor.endpoints) { // neighbor hub's neighbor
                if (neighbor_int == rm_node.number)
                    continue;
            }
        }
    }

    std::cout << "core size: " << nodes_to_remove.size() << "; # of bags: " << num_nodes - nodes_to_remove.size() << std::endl;

    return 0;
}