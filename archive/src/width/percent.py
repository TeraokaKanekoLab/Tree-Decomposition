import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]
    filepath = "output/width/mdh-"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    percents1 = []
    cnts1 = []
    length = len(lines)
    percents = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[0])
        percent = float(line.split()[6])
        widths1.append(width1)
        percents1.append(percent)
        cnts1.append(percent)

    filepath = "output/width/sbr-" + arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    cnts2 = []
    for line in lines:
        width = int(line.split()[0])
        percent = float(line.split()[6])
        widths2.append(width)
        cnts2.append(percent)

    filepath = "output/width/dmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    cnts3 = []
    for line in lines:
        width = int(line.split()[0])
        percent = float(line.split()[6])
        widths3.append(width)
        cnts3.append(percent)

    filepath = "output/width/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths4 = []
    cnts4 = []
    for line in lines:
        width = int(line.split()[0])
        percent = float(line.split()[6])
        widths4.append(width)
        cnts4.append(percent)
    return widths1, cnts1, widths2, cnts2, widths3, cnts3, widths4, cnts4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4,  filename):
    plt.plot(x_axis1, y_axis1, c="r",  label="MDH")
    plt.plot(x_axis2, y_axis2,  c="g",  label="SBR")
    plt.plot(x_axis3, y_axis3, c="b",  label="DMDH")
    plt.plot(x_axis4, y_axis4, c="c",  label="LMDH")
    width = sys.argv[2]
    saved_name = "charts/width/percent/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("percent")
    plt.title("% of removed nodes per visited nodes over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, cnts1, widths2, cnts2, widths3, cnts3, widths4, cnts4, filename = read_file()
    draw_chart(widths1, cnts1, widths2, cnts2, widths3,
               cnts3, widths4, cnts4,  filename)
