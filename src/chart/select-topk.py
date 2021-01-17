import sys
import numpy as np
import matplotlib as mp
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filename = sys.argv[1]
    arg_width = sys.argv[2]

    filepath = "output/select-topk/"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    per_a = []
    cnta1 = []
    cnta5 = []
    cnta10 = []
    cnta15 = []
    for line in lines:
        per = float(line.split()[0])
        cnt1 = float(line.split()[1])
        cnt5 = float(line.split()[2])
        cnt10 = float(line.split()[3])
        cnt15 = float(line.split()[4])
        per_a.append(per)
        cnta1.append(cnt1)
        cnta5.append(cnt5)
        cnta10.append(cnt10)
        cnta15.append(cnt15)

    return per_a, cnta1, cnta5, cnta10, cnta15


def draw_chart(x_axis, y_axis1, y_axis2, y_axis3, y_axis4):
    xlim = 100
    plt.xticks([i/10 * xlim for i in range(11)], [str(i/10 * xlim)
                                                  for i in range(11)])
    plt.yticks([i for i in range(0, 101, 10)], [str(i)
                                                for i in range(0, 101,  10)])
    plt.plot(x_axis, y_axis1,  c="r",  label="induced subtree size", zorder=10)
    plt.plot(x_axis, y_axis3,  c="b", label="degree", zorder=5)
    plt.plot(x_axis, y_axis2,  c="g", label="furthest descendant", zorder=1)
    plt.plot(x_axis, y_axis4,  c="y", label="2ISS-DEG")
    plt.grid(ls='--')
    filename = sys.argv[1]
    width = sys.argv[2]
    saved_name = "charts/select-topk/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, xlim)
    plt.ylim(0, 100)
    plt.xlabel("top x %")
    plt.ylabel("Accuracy Rate")
    plt.title(filename)
    plt.legend(loc="lower right", fontsize=8)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    per_a, cnta1, cnta5, cnta10, cnta15 = read_file()
    draw_chart(per_a, cnta1, cnta5, cnta10, cnta15)
