#include "../graph.hpp"

int main(int argc, char* argv[])
{
    Graph g;
    g.read_graph("graph/com-amazon.gr");

    int nd1 = 2, nd2 = 34;
    cout << "eccentricity(" << nd1 << ") = " << g.compute_eccentricity(nd1) << endl;
    return 0;
}