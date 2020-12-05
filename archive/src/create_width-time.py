import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filepath = sys.argv[1]
    arg_width = sys.argv[2]

    idx = filepath.find("output/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".txt")]
    filepath = "output/"+arg_width+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    times1 = []
    total = 0
    length = len(lines)
    for i in range(1, length):
        line = lines[i]
        width = int(line.split()[0])
        time = float(line.split()[2])
        total += time
        widths1.append(width)
        times1.append(total)

    filepath = "output/"+arg_width+"-mdh-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    times2 = []
    total = 0
    length = len(lines)
    for i in range(0, length):
        line = lines[i]
        width = int(line.split()[0])
        time = float(line.split()[2])
        total += time
        widths2.append(width)
        times2.append(total)
    return widths1, times1, widths2, times2, filename, path


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, filename, path):
    plt.plot(x_axis1, y_axis1,  c="r",  label="SBR")
    plt.plot(x_axis2, y_axis2,  c="b",  label="MDH")
    width = sys.argv[2]
    saved_name = path + "charts/time/integrated-" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("time consumption [s]")
    plt.title("time consumption over width: " + filename)
    plt.legend(loc="upper left", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, times1, widths2, times2, filename, path = read_file()
    draw_chart(widths1, times1, widths2, times2, filename, path)
