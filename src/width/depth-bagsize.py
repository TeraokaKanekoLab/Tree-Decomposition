import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <depth>")
        exit()

    filename = sys.argv[1]
    arg_depth = sys.argv[2]
    filepath = "output/depth-bagsize/mdh-"+arg_depth+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    depths1 = []
    bagsizes1 = []
    cnts1 = []
    for line in lines:
        depth1 = int(line.split()[0])
        bagsize = int(line.split()[1])
        depths1.append(depth1)
        bagsizes1.append(bagsize)
        cnts1.append(bagsize)

    filepath = "output/depth-bagsize/sbr-" + arg_depth+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    depths2 = []
    cnts2 = []
    for line in lines:
        depth = int(line.split()[0])
        bagsize = int(line.split()[1])
        depths2.append(depth)
        cnts2.append(bagsize)

    filepath = "output/depth-bagsize/dmdh-" + arg_depth + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    depths3 = []
    cnts3 = []
    for line in lines:
        depth = int(line.split()[0])
        bagsize = int(line.split()[1])
        depths3.append(depth)
        cnts3.append(bagsize)

    filepath = "output/depth-bagsize/lmdh-" + arg_depth + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    depths4 = []
    cnts4 = []
    for line in lines:
        depth = int(line.split()[0])
        bagsize = int(line.split()[1])
        depths4.append(depth)
        cnts4.append(bagsize)
    return depths1, cnts1, depths2, cnts2, depths3, cnts3, depths4, cnts4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4,  filename):
    plt.scatter(x_axis1, y_axis1, c="r",  label="MDH")
    plt.scatter(x_axis2, y_axis2,  c="g",  label="SBR")
    plt.scatter(x_axis3, y_axis3, c="b",  label="DMDH")
    plt.scatter(x_axis4, y_axis4, c="c",  label="LMDH")
    depth = sys.argv[2]
    saved_name = "charts/depth-bagsize/" + depth + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(depth))
    plt.ylim(bottom=0)
    plt.xlabel("depth")
    plt.ylabel("bagsize")
    plt.title("bagsize over depth: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    depths1, cnts1, depths2, cnts2, depths3, cnts3, depths4, cnts4, filename = read_file()
    draw_chart(depths1, cnts1, depths2, cnts2, depths3,
               cnts3, depths4, cnts4,  filename)
