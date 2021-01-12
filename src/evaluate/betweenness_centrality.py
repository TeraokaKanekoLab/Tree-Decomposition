import networkx as nx
from networkx.algorithms.centrality import betweenness_centrality
import sys


def read_graph():
    filepath = "graph/" + sys.argv[1] + ".gr"
    graph = nx.Graph()
    f = open(filepath, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        if left == right:
            continue
        graph.add_edge(left, right)
        graph.add_edge(right, left)
    f.close()
    return graph


def write_to_file(bcs):
    saved_name = "output/betweenness_centrality/" + sys.argv[1] + ".bc"
    f = open(saved_name, "w")
    for key in bcs:
        line = str(key) + " " + str(bcs[key]) + "\n"
        f.write(line)


if __name__ == "__main__":
    graph = read_graph()
    bcs = betweenness_centrality(graph)
    write_to_file(bcs)
