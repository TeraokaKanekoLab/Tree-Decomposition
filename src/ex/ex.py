from networkx.algorithms.distance_measures import eccentricity, diameter
import networkx as nx


def read_graph():
    filepath = "graph/com-amazon.gr"
    graph = nx.Graph()
    f = open(filepath, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        graph.add_edge(left, right)
        graph.add_edge(right, left)
    return graph


if __name__ == "__main__":
    graph = read_graph()

    nd1 = 2
    nd2 = 34
    # dist_in_graph = find_path(graph, nd1, nd2)[3]
    # print("dist(" + str(nd1) + ", " + str(nd2) + ") = " + str(dist_in_graph))\
    eccentricity = eccentricity(graph, nd1)
    print("eccentricity(" + str(nd1) + ") = " + str(eccentricity))
