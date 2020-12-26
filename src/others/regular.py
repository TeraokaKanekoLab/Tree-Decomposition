import networkx as nx

degree = 3

filename = "graph/" + str(degree) + "-regular.gr"
print(filename)
f = open(filename, "w")
G = nx.generators.random_graphs.random_regular_graph(degree, 1000000)
for edge in G.edges:
    e = str(edge[0]) + " " + str(edge[1]) + "\n"
    f.write(e)
