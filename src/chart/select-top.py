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

    filepath = "output/select-top/"+arg_width+"-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    per_a = []
    cnta1 = []
    cnta5 = []
    cnta10 = []
    cnta15 = []
    cnta20 = []
    cnta25 = []
    for line in lines:
        per = float(line.split()[0])
        cnt1 = float(line.split()[1])
        cnt5 = float(line.split()[2])
        cnt10 = float(line.split()[3])
        cnt15 = float(line.split()[4])
        cnt20 = float(line.split()[5])
        cnt25 = float(line.split()[6])
        per_a.append(per)
        cnta1.append(cnt1)
        cnta5.append(cnt5)
        cnta10.append(cnt10)
        cnta15.append(cnt15)
        cnta20.append(cnt20)
        cnta25.append(cnt25)

    return per_a, cnta1, cnta5, cnta10, cnta15, cnta20, cnta25


def draw_chart(x_axis, y_axis1, y_axis2, y_axis3, y_axis4, y_axis5, y_axis6):
    plt.xticks([i for i in range(0, 101, 10)], [str(i)
                                                for i in range(0, 101, 10)])
    plt.yticks([i for i in range(0, 101, 10)], [str(i)
                                                for i in range(0, 101, 10)])
    # plt.plot(x_axis, y_axis1,  c="r",  label="1%")
    plt.plot(x_axis, y_axis2,  c="g", label="5%")
    plt.plot(x_axis, y_axis3,  c="b", label="10%")
    plt.plot(x_axis, y_axis4,  c="c", label="15%")
    plt.plot(x_axis, y_axis5,  c="m", label="20%")
    plt.plot(x_axis, y_axis6,  c="y", label="25%")
    plt.grid(ls='--')
    filename = sys.argv[1]
    width = sys.argv[2]
    saved_name = "charts/select-top/" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, 100)
    plt.ylim(0, 100)
    plt.xlabel("top x % with highest betweenness centrality")
    plt.ylabel("% of included nodes")
    plt.title(filename)
    plt.legend(loc="lower right", fontsize=8)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    per_a, cnta1, cnta5, cnta10, cnta15, cnta20, cnta25 = read_file()
    draw_chart(per_a, cnta1, cnta5, cnta10, cnta15, cnta20, cnta25)
