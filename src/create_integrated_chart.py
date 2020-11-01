import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 2:
        print("usage: python3", sys.argv[0], "<filename>")
        exit()

    filepath = sys.argv[1]
    f = open(filepath, "r")
    idx = filepath.find("output/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".txt")]
    lines = f.readlines()
    widths1 = []
    num_nodes1 = []
    for line in lines:
        width1, num_node = map(int, line.split())
        widths1.append(width1)
        num_nodes1.append(num_node)

    filepath = "output/random-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    num_nodes2 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths2.append(width)
        num_nodes2.append(num_node)
    return widths1, num_nodes1, widths2, num_nodes2, path, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, path, filename):
    plt.plot(x_axis1, y_axis1,  c="b",  label="optimal")
    plt.plot(x_axis2, y_axis2, c="r",  label="random")
    saved_name = path + "charts/integrated-" + filename + ".pdf"
    print(saved_name)
    # plt.xlim(0, 100)
    # plt.ylim(0, 310000)
    plt.xlabel("width")
    plt.ylabel("% of removed nodes")
    plt.title("% of removed nodes over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    width_array1, num_nodes1, width_array2, num_nodes2, path, filename = read_file()
    draw_chart(width_array1, num_nodes1, width_array2,
               num_nodes2, path, filename)
