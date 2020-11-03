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
    percentages1 = []
    length = len(lines)
    num_nodes = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1, num_node = map(int, line.split())
        widths1.append(width1)
        num_nodes1.append(num_node)
        percentages1.append(num_node/num_nodes * 100)

    filepath = "output/random-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    num_nodes2 = []
    percentages2 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths2.append(width)
        num_nodes2.append(num_node)
        percentages2.append(num_node/num_nodes * 100)

    filepath = "degree/"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    num_nodes3 = []
    percentages3 = []
    current_ne = 0
    num_edges = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        deg, num_node = map(int, line.split())
        widths3.append(deg)
        num_nodes3.append(num_node)
        current_ne += num_node
        percentages3.append(current_ne/num_nodes * 100)
    return widths1, percentages1, widths2, percentages2, widths3, percentages3, path, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, path, filename):
    plt.plot(x_axis1, y_axis1,  c="b",  label="optimal")
    plt.plot(x_axis2, y_axis2, c="r",  label="random")
    plt.plot(x_axis3, y_axis3, c="g",  label="degree")
    saved_name = path + "charts/integrated-" + filename + ".pdf"
    print(saved_name)
    # plt.xlim(0, 100)
    plt.ylim(0, 100)
    plt.xlabel("width/degree")
    plt.ylabel("% of removed nodes")
    plt.title("% of removed nodes over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, percentages1, widths2, percentages2, widths3, percentages3, path, filename = read_file()
    draw_chart(widths1, percentages1, widths2, percentages2,
               widths3, percentages3, path, filename)
