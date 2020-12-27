import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]

    filepath = "output/start/dmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    degree1 = []
    cnts3 = []
    for line in lines:
        degree = int(line.split()[0])
        strahler = int(line.split()[7])
        degree1.append(degree)
        cnts3.append(strahler)

    filepath = "output/start/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    degree2 = []
    cnts4 = []
    for line in lines:
        width = int(line.split()[0])
        strahler = int(line.split()[7])
        degree2.append(width)
        cnts4.append(strahler)
    return degree1, cnts3, degree2, cnts4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, filename):
    plt.scatter(x_axis2, y_axis2,  c="g",  label="LMDH")
    plt.scatter(x_axis1, y_axis1, c="r",  label="DMDH")
    width = sys.argv[2]
    saved_name = "charts/start/strahler/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.ylim(bottom=0)
    plt.xlabel("origin degree")
    plt.ylabel("strahler #")
    plt.title("strahler # over origin degree of width " +
              width + ": " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    degree1, cnts3, degree2, cnts4, filename = read_file()
    draw_chart(degree1, cnts3, degree2, cnts4, filename)
