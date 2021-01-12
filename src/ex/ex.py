import networkx as nx
from networkx.algorithms.distance_measures import eccentricity, diameter
from networkx.algorithms.cluster import average_clustering
from networkx.algorithms.centrality import betweenness_centrality
import sys


def read_graph():
    # filepath = "graph/com-amazon.gr"
    # filepath = "graph/fb-pages-food.gr"
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


def generate_connected_graph(s):
    filepath = "graph/" + sys.argv[1] + ".gr"
    filepath2 = "graph/" + sys.argv[1] + "-connected.gr"
    f = open(filepath, "r")
    f2 = open(filepath2, "w")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        if left == right:
            continue
        if left in s or right in s:
            f2.write(line)


if __name__ == "__main__":
    graph = read_graph()

    nd1 = 2
    nd2 = 34
    # dist_in_graph = find_path(graph, nd1, nd2)[3]
    # print("dist(" + str(nd1) + ", " + str(nd2) + ") = " + str(dist_in_graph))\
    # eccentricity = eccentricity(graph, nd1)
    # print("average_clustering(" + str(nd1) + ") = " + str(x))
    graphs = nx.algorithms.components.connected_components(graph)
    for g in graphs:
        s = g
        break
    generate_connected_graph(s)
    # x = diameter(graph)
    # print("diameter() = " + str(x))
    # x = betweenness_centrality(graph)
    # print("average_clustering() = " + str(x))
