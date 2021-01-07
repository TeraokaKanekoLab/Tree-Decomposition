import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]
    filepath = "output/step/mdh-"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    strahlers1 = []
    strahlers1 = []
    length = len(lines)
    num_nodes = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[1])
        strahler = int(line.split()[7])
        widths1.append(width1/num_nodes)
        strahlers1.append(strahler)

    filepath = "output/step/sbr-" + arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    strahlers2 = []
    for line in lines:
        width = int(line.split()[1])
        strahler = int(line.split()[7])
        widths2.append(width/num_nodes)
        strahlers2.append(strahler)

    filepath = "output/step/dmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    strahlers3 = []
    for line in lines:
        width = int(line.split()[1])
        strahler = int(line.split()[7])
        widths3.append(width/num_nodes)
        strahlers3.append(strahler)

    filepath = "output/step/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths4 = []
    strahlers4 = []
    for line in lines:
        width = int(line.split()[1])
        strahler = int(line.split()[7])
        widths4.append(width/num_nodes)
        strahlers4.append(strahler)
    return widths1, strahlers1, widths2, strahlers2, widths3, strahlers3, widths4, strahlers4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4,  filename):
    plt.plot(x_axis1, y_axis1, c="r",  label="MDH")
    plt.plot(x_axis2, y_axis2,  c="g",  label="SBR")
    plt.plot(x_axis3, y_axis3, c="b",  label="DMDH")
    plt.plot(x_axis4, y_axis4, c="c",  label="LMDH")
    width = sys.argv[2]
    saved_name = "charts/step/strahler/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, 1)
    plt.ylim(bottom=0)
    plt.xlabel("remove rate")
    plt.ylabel("strahler number")
    plt.title("strahler number over remove rate of width " +
              width + ": " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, strahlers1, widths2, strahlers2, widths3, strahlers3, widths4, strahlers4, filename = read_file()
    draw_chart(widths1, strahlers1, widths2, strahlers2, widths3,
               strahlers3, widths4, strahlers4,  filename)
