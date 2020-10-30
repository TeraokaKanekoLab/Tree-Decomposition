import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 2:
        print("usage: python3", sys.argv[0], "<filename>")
        exit()

    filepath = sys.argv[1]
    f = open(filepath, "r")
    idx = filepath.find("degree/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".txt")]
    lines = f.readlines()
    widths = []
    num_nodes = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths.append(width)
        num_nodes.append(num_node)
    return widths, num_nodes, path, filename


def draw_chart(x_axis, y_axis, path, filename):
    plt.scatter(x_axis, y_axis)
    plt.xlim(0, 100)
    plt.ylim(0, 20000)
    saved_name = path + "degree/charts/" + filename + ".pdf"
    print(saved_name)
    plt.xlabel("degree")
    plt.ylabel("number of nodes")
    plt.title("Degree distribution of "+filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    width_array, num_nodes, path, filename = read_file()
    draw_chart(width_array, num_nodes, path, filename)
