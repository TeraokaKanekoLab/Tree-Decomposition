import sys
import matplotlib.pyplot as plt
import networkx as nx

IS_PLOT = True


def read_graph(filepath):
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


def draw_chart(data_to_plot, x_tick_label, saved_name):
    print(saved_name)
    fig, axes = plt.subplots(figsize=(12, 8))
    plt.boxplot(data_to_plot, sym='')
    axes.set_xticklabels(x_tick_label)
    plt.xlabel("node id")
    plt.ylabel("degree")
    # plt.title(y_axis_title + " over " + x_axis_title + ": " + filename)
    plt.savefig(saved_name)


def read_file(filepath):
    f = open(filepath, "r")
    lines = f.readlines()
    x_axis = []
    y_axis = []
    s = set()
    for line in lines:
        left = int(line.split()[0])
        right = float(line.split()[1])
        if (left, right) in s:
            continue
        x_axis.append(left)
        y_axis.append(right)
        s.add((left, right))
    return x_axis, y_axis


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4, saved_name):
    plt.plot(x_axis1, y_axis1, c="r", label="53213")
    plt.plot(x_axis2, y_axis2, c="g", label="35290")
    plt.plot(x_axis3, y_axis3, c="b", label="38109")
    plt.plot(x_axis4, y_axis4, c="y", label="1086")
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel("degree of neighbors")
    plt.ylabel("#nodes")
    plt.title("degree distribution of neighbors of each node")
    plt.legend(loc="lower right", fontsize=8)  # (7)凡例表示
    plt.savefig(saved_name)


def plot():
    files = ["53213", "35290", "38109", "1086"]
    X = []
    Y = []
    for file in files:
        filepath = "output/nbr-deg/" + file + "-ca-astroph-connected.output"
        x, y = read_file(filepath)
        X.append(x)
        Y.append(y)

    draw_chart(X[0], Y[0], X[1], Y[1], X[2], Y[2],
               X[3], Y[3], "charts/nbr-deg/yeah.pdf")


if __name__ == '__main__':
    if IS_PLOT:
        plot()
        exit()
    nodes = [53213, 35290, 38109, 62821, 93504, 92790, 21718, 1086]
    graph = read_graph("graph/ca-astroph-connected.gr")
    data_to_plot = []
    for node in nodes:
        data = []
        for nbr in graph.neighbors(node):
            data.append(graph.degree[nbr])
        data_to_plot.append(data)

    draw_chart(data_to_plot, map(str, nodes), "charts/nbr-deg/yeah.pdf")
