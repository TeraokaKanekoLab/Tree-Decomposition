import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 2:
        print("usage: python3", sys.argv[0], "<filename>")
        exit()

    f = open(sys.argv[1], "r")
    lines = f.readlines()
    widths = []
    num_nodes = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths.append(width)
        num_nodes.append(num_node)
    return widths, num_nodes


def draw_chart(x_axis, y_axis):
    plt.plot(x_axis, y_axis)
    plt.show()


if __name__ == '__main__':
    width_array, num_nodes = read_file()
    draw_chart(width_array, num_nodes)
