import sys
from dijkstar import Graph, find_path
import random
import matplotlib.pyplot as plt

LIMIT = 10


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


def write_to_file(x_axis, y_axis):
    saved_name = "output/read_tree/" + arg_width + \
        "-" + filename + "-" + str(LIMIT) + ".output"
    f = open(saved_name, "w")
    for x, y in zip(x_axis, y_axis):
        line = str(x) + " " + str(y) + "\n"
        f.write(line)


def read_tree():
    filepath = "tree/" + arg_width+"-"+filename+".tree"
    f = open(filepath, "r")
    lines = f.readlines()
    length = len(lines)
    if lines[0].split()[0] != "core":
        root = int(lines[0])
        root_node = str(root)
        for i in lines[1].split():
            root_node += " " + i
        d[root] = root_node
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


def find_dist_in_tree(parents, nd1, nd2):
    nd = nd1
    path1 = []
    path2 = []
    while nd != -1:
        path1.append(nd)
        nd = parents[nd]
    path1.append(-1)
    path1.reverse()
    nd = nd2
    while nd != -1:
        path2.append(nd)
        nd = parents[nd]
    path2.append(-1)
    path2.reverse()
    same_cnt = 0
    dist = 0
    for p1, p2 in zip(path1, path2):
        if p1 == p2:
            same_cnt += 1
    dist += len(path1) - same_cnt
    dist += len(path2) - same_cnt
    return dist


def draw_chart(x_axis1, y_axis1):
    plt.scatter(x_axis1, y_axis1, c="r")
    width = sys.argv[2]
    saved_name = "charts/tree-graph/" + arg_width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel("distance in tree")
    plt.ylabel("distance in graph")
    plt.title("distance in graph over distance in tree " +
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
    for _ in range(LIMIT):
        nd1 = random.choice(bags)
        nd2 = random.choice(bags)
        dist_in_tree = find_dist_in_tree(parents, nd1, nd2)
        dist_in_graph = find_path(graph, nd1, nd2)[3]
        tree_dists.append(dist_in_tree)
        graph_dists.append(dist_in_graph)
        print("node " + str(nd1) + " node " + str(nd2) + " tree: " +
              str(dist_in_tree) + ", graph : " + str(dist_in_graph))
    write_to_file(tree_dists, graph_dists)
    draw_chart(tree_dists, graph_dists)
