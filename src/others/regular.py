import networkx as nx
from networkx.classes.function import number_of_nodes

degree = 10
num_nodes = 1000000

filename = "graph/" + str(degree) + "-regular-" + str(num_nodes) + ".gr"
print(filename)
f = open(filename, "w")
G = nx.generators.random_graphs.random_regular_graph(degree, num_nodes)
for edge in G.edges:
    e = str(edge[0]) + " " + str(edge[1]) + "\n"
    f.write(e)
