from typing import Counter
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
    return graph


if __name__ == "__main__":
    graph = read_graph()
    degs = []
    for nd in graph.nodes:
        degs.append(graph.degree(nd))
    c = Counter(degs)
    degs = list(c.items())
    degs.sort(reverse=True)
    print("{", end='')
    for deg in degs:
        if deg[1] < 2:
            continue
        if deg[0] == 2:
            print(deg[0], end='')
            break
        msg = str(deg[0]) + ", "
        print(msg, end='')
    print("}")
