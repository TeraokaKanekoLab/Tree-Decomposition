import sys
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]

    filepath = "output/select_top/"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    per_a = []
    size_a = []
    dist_a = []
    for line in lines:
        per = float(line.split()[0])
        size = float(line.split()[1])
        dist = float(line.split()[2])
        per_a.append(per)
        size_a.append(size)
        dist_a.append(dist)

    return per_a, size_a, per_a, dist_a


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2):
    plt.xticks([i for i in range(0, 101, 10)], [str(i)
                                                for i in range(0, 101, 10)])
    plt.yticks([i for i in range(0, 101, 10)], [str(i)
                                                for i in range(0, 101, 10)])
    plt.plot(x_axis1, y_axis1,  c="r",  label="Chosen by Induced Subtree Size")
    plt.plot(x_axis2, y_axis2,  c="b",
             label="Chosen by Distance from Furthest Descendant")
    filename = sys.argv[1]
    width = sys.argv[2]
    saved_name = "charts/select_top/" + "10" + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, 100)
    plt.ylim(0, 100)
    plt.xlabel("top x % with highest betweenness eccentricity")
    plt.ylabel("% of included nodes")
    plt.title(filename)
    plt.legend(loc="lower right", fontsize=8)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    per_a, size_a, per_a, dist_a = read_file()
    draw_chart(per_a, size_a, per_a, dist_a)
