import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]

    filepath = "output/l-max-dh/" + arg_width + "-" + filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    times1 = []
    total_time = 0
    for line in lines:
        width = int(line.split()[1])
        time = float(line.split()[2])
        total_time += time
        widths1.append(width)
        times1.append(total_time)
    return widths1, times1, filename


def draw_chart(x_axis1, y_axis1, filename):
    plt.plot(x_axis1, y_axis1, c="r",  label="l-max-dh")
    width = sys.argv[2]
    saved_name = "charts/l-max-dh/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("# of removed nodes")
    plt.ylabel("consumed time [s]")
    plt.title("consumed time over # of removed nodes: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, times1, filename = read_file()
    draw_chart(widths1, times1, filename)
