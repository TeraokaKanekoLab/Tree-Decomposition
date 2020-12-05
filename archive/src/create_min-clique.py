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
    filepath = "output/"+arg_width+"-mdh-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths = []
    times1 = []
    total1 = 0
    times2 = []
    total2 = 0
    times_all = []
    total_all = 0
    length = len(lines)
    for line in lines:
        width = int(line.split()[0])
        time_all = float(line.split()[2])
        time1 = float(line.split()[3])
        time2 = float(line.split()[4])
        total_all += time_all
        total1 += time1
        total2 += time2
        widths.append(width)
        times_all.append(total_all)
        times1.append(total1)
        times2.append(total2)
    return widths, times_all, times1, times2, filename, path


def draw_chart(x_axis, y_axis1, y_axis2, y_axis3, filename, path):
    plt.plot(x_axis, y_axis1,  c="r",  label="all")
    plt.plot(x_axis, y_axis2,  c="g",  label="min degree")
    plt.plot(x_axis, y_axis3,  c="b",  label="clique")
    width = sys.argv[2]
    saved_name = path + "charts/time/min-deg-clique-" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(bottom=0)
    plt.xlabel("width")
    plt.ylabel("time consumption [s]")
    plt.title("time consumption over width: " + filename)
    plt.legend(loc="upper left", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths, times_all, times1, times2, filename, path = read_file()
    draw_chart(widths, times_all, times1, times2, filename, path)
