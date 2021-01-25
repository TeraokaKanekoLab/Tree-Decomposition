import matplotlib.pyplot as plt
import numpy as np

CHART_TYPES = ["degree"]

GRPAHS = ["ca-GrQc", "ca-AstroPh", "email-Enron", "soc-Slashdot"]

POS = -1


def read_file(filename):
    filepath = "output/select-top/1000000-"+filename+".output"
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
    return per_a, [cnta1, cnta5, cnta10, cnta15, cnta20, cnta25]


def draw_chart(X, Y, chart_type):
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    saved_name = "charts_for_paper/charts/" + chart_type + "-select-top.pdf"
    print(saved_name)
    for i in range(2):
        for j in range(2):
            ax = axes[i, j]
            index = 2*i + j
            ax.set_title(GRPAHS[index])
            ax.set_xticks([i for i in range(0, 101, 10)])
            ax.set_yticks([i for i in range(0, 101, 10)])
            ax.plot(X[index], Y[index][0],  c="r",  label="1%")
            ax.plot(X[index], Y[index][1],  c="g", label="5%")
            ax.plot(X[index], Y[index][2],  c="b", label="10%")
            ax.plot(X[index], Y[index][3],  c="c", label="15%")
            ax.plot(X[index], Y[index][4],  c="m", label="20%")
            ax.plot(X[index], Y[index][5],  c="y", label="25%")
            ax.grid(ls='--')
            ax.set_xlim(0, 100)
            ax.set_ylim(0, 100)
            ax.set_xlabel("top x % with highest betweenness centrality")
            ax.set_ylabel("% included nodes")
            ax.legend(loc="lower right", fontsize=8)  # (7)凡例表示
    plt.savefig(saved_name)


def correl(x, y):
    return np.corrcoef(x, y)[0, 1]


if __name__ == '__main__':
    filenames = ["ca-grqc-connected", "ca-astroph-connected",
                 "email-enron-connected", "soc-slashdot"]
    X = []
    Y = []
    chart_type = CHART_TYPES[-1]
    for filename in filenames:
        x_axis, y_axis = read_file(filename)
        X.append(x_axis)
        Y.append(y_axis)
    draw_chart(X, Y, chart_type)
