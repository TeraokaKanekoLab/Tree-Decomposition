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
    filepath = "tree/" + type + "-"+arg_width+"-"+filename+".tree"
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
        for j in map(int, lines[i*3 + 1].split()):
            if nd in childrens:
                childrens[nd].append(j)
            else:
                childrens[nd] = [j]
        parent = int(lines[i*3 + 2])
        if parent in parents:
            parents[nd] = parent
        else:
            parents[nd] = -1
    return parents, childrens, bags


def find_dist_from_leaf(childrens, nd):
    max = 0
    if nd not in childrens:
        return 0
    for child in childrens[nd]:
        d = find_dist_from_leaf(childrens, child) + 1
        if d > max:
            max = d
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
    plt.title("distance in graph over distance from leaf in leaf " +
              width + ": " + filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("usage: python3", sys.argv[0], "<type> <filename> <width>")
        exit()
    d = dict()
    type = sys.argv[1]
    filename = sys.argv[2]
    arg_width = sys.argv[3]
    print("loading...")
    parents, childrens, bags = read_tree()
    graph = read_graph()
    tree_dists = []
    graph_dists = []
    cnt = 0
    while cnt < LIMIT:
        nd1 = random.choice(bags)
        nd2 = parents[nd1]
        if nd2 < 0:
            continue
        print(str(nd1), "calculating... ")
        dist_from_leaf = find_dist_from_leaf(childrens, nd1)
        dist_in_graph = find_path(graph, nd1, nd2)[3]
        tree_dists.append(dist_from_leaf)
        graph_dists.append(dist_in_graph)
        print("dist from leaf: " + str(dist_from_leaf) +
              ", dist in graph: " + str(dist_in_graph))
        cnt += 1
    write_to_file(tree_dists, graph_dists)
    draw_chart(tree_dists, graph_dists)
