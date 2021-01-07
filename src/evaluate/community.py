import sys
from dijkstar import Graph, find_path
import random
import matplotlib.pyplot as plt

LIMIT = 1000


def read_file():
    filepath = "output/community/" + arg_width+"-" + filename + ".output"
    f = open(filepath, "r")
    lines = f.readlines()
    com_sizes = []
    subt_sizes = []
    for line in lines:
        left = int(line.split()[0])
        right = int(line.split()[1])
        com_sizes.append(left)
        subt_sizes.append(right)
    return com_sizes, subt_sizes


def draw_chart(x_axis1, y_axis1):
    plt.scatter(x_axis1, y_axis1, c="r")
    width = sys.argv[2]
    saved_name = "charts/community/" + arg_width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel("community size")
    plt.ylabel("subtree size")
    plt.title("subtree size over community size; " +
              width + ": " + filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()
    filename = sys.argv[1]
    arg_width = sys.argv[2]

    com_sizes, subt_sizes = read_file()
    draw_chart(com_sizes, subt_sizes)
