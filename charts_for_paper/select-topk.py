import matplotlib.pyplot as plt
import numpy as np


def color_normalize(r, g, b):
    return [r/256, g/256, b/256]


RED = color_normalize(219, 68, 55)
GREEN = color_normalize(15, 157, 88)
BLUE = color_normalize(66, 133, 244)
YELLOW = color_normalize(244, 160, 0)
BLACK = color_normalize(59, 59, 59)
CHART_TYPES = ["degree"]

GRPAHS = ["ca-GrQc", "ca-AstroPh", "email-Enron", "soc-Slashdot"]


def read_file(filename):
    filepath = "output/select-topk/1000000-"+filename+".output"
    f = open(filepath, "r")
    lines = f.readlines()
    per_a = []
    cnta1 = []
    cnta5 = []
    cnta10 = []
    cnta15 = []
    cnta20 = []
    for line in lines:
        per = float(line.split()[0])
        cnt1 = float(line.split()[1])
        cnt5 = float(line.split()[2])
        cnt10 = float(line.split()[3])
        cnt15 = float(line.split()[4])
        cnt20 = float(line.split()[5])
        per_a.append(per)
        cnta1.append(cnt1)
        cnta5.append(cnt5)
        cnta10.append(cnt10)
        cnta15.append(cnt15)
        cnta20.append(cnt20)
    return per_a, [cnta1, cnta5, cnta10, cnta15, cnta20]


def draw_chart(X, Y, chart_type):
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    saved_name = "charts_for_paper/charts/select-topk.pdf"
    print(saved_name)
    for i in range(2):
        for j in range(2):
            ax = axes[i, j]
            index = 2*i + j
            ax.set_title(GRPAHS[index])
            ax.set_xticks([i for i in range(0, 101, 10)])
            ax.set_yticks([i for i in range(0, 101, 10)])
            ax.plot(X[index], Y[index][0],  c="r",  label="ISS", zorder=50)
            ax.plot(X[index], Y[index][2],  c="b",
                    label="#Child", zorder=100)
            ax.plot(X[index], Y[index][3],  c="y",
                    label="Sum Children's #Strahler", zorder=5)
            ax.plot(X[index], Y[index][1],   c="g",
                    label="ISS + Sum Children's #Strahler", zorder=10)
            ax.plot(X[index], Y[index][4],  c="k", label="Degree", zorder=5)
            ax.grid(ls='--')
            ax.set_xlim(left=0)
            ax.set_ylim(0, 100)
            ax.set_xlabel("top x %")
            ax.set_ylabel("accuracy rate %")
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
