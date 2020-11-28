import sys
import numpy as np
import matplotlib.pyplot as plt

colors = ["b", "g", "r", "c", "m", "y", "k",
          "tab:orange", "tab:purple", "tab:brown", "tab:pink"]


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filepath = sys.argv[1]
    arg_width = sys.argv[2]
    idx = filepath.find("output/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".txt")]
    filepath = "output/"+arg_width+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths = []
    nums_nodes = []
    times = []
    length = len(lines)
    num_nodes = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width = int(line.split()[0])
        num_node = int(line.split()[1])
        time = float(line.split()[2])
        widths.append(width)
        times.append(time)
        if i == 1:
            n = num_node
        else:
            n = num_node - nums_nodes[-1]
        msg = "width: " + str(width) + ", time: " + str(time) + ", num_node: " + \
            str(n)
        print(msg)
        nums_nodes.append(num_node)
    return widths, times, filename, path


def draw_chart(x_axis, y_axis, filename, path):
    plt.scatter(x_axis, y_axis,  c="b",  label="optimal", s=1)
    width = sys.argv[2]
    saved_name = path + "charts/time/integrated-" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("time consumed from (n-1)th to nth decomposition [s]")
    plt.title("time consumption over width: " + filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths, times, filename, path = read_file()
    draw_chart(widths, times, filename, path)
