import sys
from dijkstar import Graph, find_path
import random
import matplotlib.pyplot as plt

LIMIT = 1000


def read_graph():
    filepath = "graph/" + filename+".gr"
    graph = Graph()
    f = open(filepath, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        graph.add_edge(left, right, 1)
        graph.add_edge(right, left, 1)
    return graph


def read_tree():
    filepath = "tree/" + arg_width + "-" + filename + ".tree"
    f = open(filepath, "r")
    lines = f.readlines()
    length = len(lines)
    if lines[0].split()[0] != "core":
        leaf = int(lines[0])
        leaf_node = str(leaf)
        for i in lines[1].split():
            leaf_node += " " + i
        d[leaf] = leaf_node
    parents = dict()
    childrens = dict()
    bags = []
    for i in range(1, length//3):
        nd = int(lines[i*3])
        bags.append(nd)
        parent = int(lines[i*3 + 2])
        if parent in parents:
            parents[nd] = parent
        else:
            parents[nd] = -1
        if parent in childrens:
            childrens[parent].append(nd)
        else:
            childrens[parent] = [nd]
    return parents, childrens, bags


def find_dist_from_leaf(childrens, nd, dists):
    max = 0
    if nd in dists:
        return dists[nd]
    if nd not in childrens:
        return 0
    for child in childrens[nd]:
        d = find_dist_from_leaf(childrens, child, dists) + 1
        if d > max:
            max = d
    dists[nd] = max
    return max


def write_to_file(x_axis, y_axis):
    saved_name = "output/dist_leaf/" + arg_width + \
        "-" + filename + "-" + str(LIMIT) + ".output"
    f = open(saved_name, "w")
    for x, y in zip(x_axis, y_axis):
        line = str(x) + " " + str(y) + "\n"
        f.write(line)


def draw_chart(x_axis1, y_axis1):
    plt.scatter(x_axis1, y_axis1, c="r")
    width = sys.argv[2]
    saved_name = "charts/dist_leaf/" + arg_width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel("distance from leaf")
    plt.ylabel("distance in graph")
    plt.title("distance in graph over distance from leaf in tree " +
              width + ": " + filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()
    d = dict()
    filename = sys.argv[1]
    arg_width = sys.argv[2]
    print("loading...")
    parents, childrens, bags = read_tree()
    graph = read_graph()
    tree_dists = []
    graph_dists = []
    dists = dict()
    cnt = 0
    # for nd1 in bags:
    while cnt < LIMIT:
        nd1 = random.choice(bags)
        nd2 = parents[nd1]
        if nd2 < 0:
            continue
        print(str(nd1), "calculating... ")
        dist_from_leaf = find_dist_from_leaf(childrens, nd1, dists)
        dist_in_graph = find_path(graph, nd1, nd2)[3]
        tree_dists.append(dist_from_leaf)
        graph_dists.append(dist_in_graph)
        print("dist from leaf: " + str(dist_from_leaf) +
              ", dist in graph: " + str(dist_in_graph))
        cnt += 1
    write_to_file(tree_dists, graph_dists)
    draw_chart(tree_dists, graph_dists)