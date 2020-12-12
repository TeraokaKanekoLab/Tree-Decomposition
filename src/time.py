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
    times1 = []
    times1 = []
    length = len(lines)
    # num_nodes = int(lines[0])
    total = 0
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[0])
        time = float(line.split()[2])
        total += time
        widths1.append(width1)
        times1.append(total)

    filepath = "output/sbr-" + arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    times2 = []
    total = 0
    for line in lines:
        width = int(line.split()[0])
        time = float(line.split()[2])
        total += time
        widths2.append(width)
        times2.append(total)

    filepath = "output/lmdh-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    times3 = []
    for line in lines:
        width = int(line.split()[0])
        time = float(line.split()[2])
        widths3.append(width)
        times3.append(time)

    filepath = "output/lmdh_naive-" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths4 = []
    times4 = []
    for line in lines:
        width = int(line.split()[0])
        time = float(line.split()[2])
        widths4.append(width)
        times4.append(time)
    return widths1, times1, widths2, times2, widths3, times3, widths4, times4, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4,  filename):
    plt.plot(x_axis1, y_axis1, c="r",  label="MDH")
    plt.plot(x_axis2, y_axis2,  c="g",  label="SBR")
    plt.plot(x_axis3, y_axis3, c="b",  label="LMDH")
    plt.plot(x_axis4, y_axis4, c="c",  label="LMDH naive")
    width = sys.argv[2]
    saved_name = "charts/time/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("consumed time [s]")
    plt.title("consumed time over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, times1, widths2, times2, widths3, times3, widths4, times4, filename = read_file()
    draw_chart(widths1, times1, widths2, times2, widths3,
               times3, widths4, times4,  filename)
