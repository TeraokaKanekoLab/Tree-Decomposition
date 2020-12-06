import sys
import numpy as np
import matplotlib.pyplot as plt

colors = ["b", "g", "r", "c", "m", "y", "k",
          "tab:orange", "tab:purple", "tab:brown", "tab:pink"]

graphs = ["1381622", "2492969", "26863", "2852988",
          "2899249", "3145563", "3144803", "3294444", "3958248", "401845", "9766"]


def read_file(graph, filename, arg_width):
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filepath = "walks/"+arg_width+"-"+graph+"-"+filename+".gr"
    print(filepath)
    f = open(filepath, "r")
    lines = f.readlines()
    widths = []
    num_nodes = []
    length = len(lines)
    for i in range(1, length):
        line = lines[i]
        width = int(line.split()[0])
        num_node = int(line.split()[1])
        widths.append(width)
        num_nodes.append(num_node)
    return widths, num_nodes


if __name__ == '__main__':
    filepath = sys.argv[1]
    arg_width = sys.argv[2]
    idx = filepath.find("output/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".gr")]
    plt.xlim(0, 20)
    plt.xlabel("width")
    plt.ylabel("# of nodes over width")
    plt.title("walk: " + filename)
    for graph, color in zip(graphs, colors):
        x_axis, y_axis = read_file(graph, filename, arg_width)
        print(x_axis)
        print(y_axis)
        print(graph)
        print(color)
        plt.plot(x_axis, y_axis,  c=color,  label=graph)
    saved_name = path + "walks/charts/" + arg_width + "-" + filename + ".pdf"
    plt.savefig(saved_name)
    print(saved_name)