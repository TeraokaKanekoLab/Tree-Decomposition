import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]
    filepath = "output/mdh-"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    strahlers1 = []
    cnts1 = []
    length = len(lines)
    strahlers = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[0])
        strahler = int(line.split()[7])
        widths1.append(width1)
        strahlers1.append(strahler)
        cnts1.append(strahler)

    filepath = "output/sbr-" + arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    cnts2 = []
    for line in lines:
        width = int(line.split()[0])
        strahler = int(line.split()[7])
        widths2.append(width)
        cnts2.append(strahler)

    filepath = "output/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    cnts3 = []
    for line in lines:
        width = int(line.split()[0])
        strahler = int(line.split()[7])
        widths3.append(width)
        cnts3.append(strahler)

    filepath = "output/lmdh_naive-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths4 = []
    cnts4 = []
    for line in lines:
        width = int(line.split()[0])
        strahler = int(line.split()[7])
        widths4.append(width)
        cnts4.append(strahler)
    return widths1, cnts1, widths2, cnts2, widths3, cnts3, widths4, cnts4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4,  filename):
    plt.plot(x_axis1, y_axis1, c="r",  label="MDH")
    plt.plot(x_axis2, y_axis2,  c="g",  label="SBR")
    plt.plot(x_axis3, y_axis3, c="b",  label="LMDH")
    plt.plot(x_axis4, y_axis4, c="c",  label="LMDH naive")
    width = sys.argv[2]
    saved_name = "charts/strahler/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("strahler number")
    plt.title("strahler number over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, cnts1, widths2, cnts2, widths3, cnts3, widths4, cnts4, filename = read_file()
    draw_chart(widths1, cnts1, widths2, cnts2, widths3,
               cnts3, widths4, cnts4,  filename)
