import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]
    filepath = "output/sbr-"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    num_nodes1 = []
    percentages1 = []
    length = len(lines)
    num_nodes = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[0])
        num_node = int(line.split()[1])
        widths1.append(width1)
        num_nodes1.append(num_node)
        percentages1.append(num_node/num_nodes * 100)

    filepath = "output/mdh-" + arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    percentages2 = []
    for line in lines:
        width = int(line.split()[0])
        num_node = int(line.split()[1])
        widths2.append(width)
        percentages2.append(num_node/num_nodes * 100)

    filepath = "output/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    percentages3 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths3.append(width)
        percentages3.append(num_node/num_nodes * 100)
    return widths1, percentages1, widths2, percentages2, widths3, percentages3, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, filename):
    plt.plot(x_axis2, y_axis2, c="r",  label="MDH")
    plt.plot(x_axis1, y_axis1,  c="g",  label="SBR")
    plt.plot(x_axis3, y_axis3, c="b",  label="LMDH")
    width = sys.argv[2]
    saved_name = "charts/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(0, 100)
    plt.xlabel("width")
    plt.ylabel("% of removed nodes")
    plt.title("% of removed nodes over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, percentages1, widths2, percentages2, widths3, percentages3, filename = read_file()
    draw_chart(widths1, percentages1, widths2, percentages2,
               widths3, percentages3,  filename)
