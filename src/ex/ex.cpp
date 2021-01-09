#include "../graph.hpp"

int main(int argc, char* argv[])
{
    Graph g;
    g.read_graph("graph/com-amazon.gr");

    int nd1 = 548280, nd2 = 34;
    // cout << "eccentricity(" << nd1 << ") = " << g.compute_eccentricity(nd1) << endl;
    // cout << "clustering_coefficient(" << nd1 << ") = " << g.compute_clustering_coefficient(nd1) << endl;
    cout << "average_clustering() = " << g.compute_average_clustering() << endl;
    return 0;
}