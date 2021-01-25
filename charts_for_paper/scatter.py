import matplotlib.pyplot as plt
import numpy as np

DEG = "degree"
BC = "betweenness centrality"
CC = "clustering coefficient"

CHART_TYPES = ["bc-degree", "bc-cc"]
X_TITLES = [DEG, CC]
Y_TITLES = [BC, BC]

POS = -1

GRPAHS = ["ca-GrQc", "ca-AstroPh", "email-Enron", "soc-Slashdot"]


def read_file(filename, chart_type):
    filepath = "output/" + chart_type + "/1000000-" + filename + ".output"
    f = open(filepath, "r")
    lines = f.readlines()
    x_axis = []
    y_axis = []
    s = set()
    for line in lines:
        left = float(line.split()[0])
        right = float(line.split()[1])
        if (left, right) in s:
            continue
        x_axis.append(left)
        y_axis.append(right)
        s.add((left, right))
    return x_axis, y_axis


def draw_chart(X, Y, chart_type, x_title, y_title):
    MARKER_SIZE = 10
    MARKER_COLOR = "blue"
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    saved_name = "charts_for_paper/charts/" + chart_type + "-scatter.pdf"
    print(saved_name)
    for i in range(2):
        for j in range(2):
            ax = axes[i, j]
            index = 2*i + j
            ax.set_title(GRPAHS[index])
            ax.scatter(X[index], Y[index], c=MARKER_COLOR,
                       s=MARKER_SIZE, zorder=100)
            ax.set_xlim(left=0)
            ax.set_ylim(bottom=0)
            ax.set_xlabel(x_title)
            ax.set_ylabel(y_title)
            ax.grid(ls='--')
    plt.savefig(saved_name)


def correl(x, y):
    return np.corrcoef(x, y)[0, 1]


if __name__ == '__main__':
    if len(CHART_TYPES) == len(X_TITLES) == len(Y_TITLES):
        chart_type = CHART_TYPES[POS]
        x_title = X_TITLES[POS]
        y_title = Y_TITLES[POS]
    else:
        print("error! check type, x title, and y title")
        exit(-1)
    filenames = ["ca-grqc-connected", "ca-astroph-connected",
                 "email-enron-connected", "soc-slashdot"]
    X = []
    Y = []
    for filename in filenames:
        x_axis, y_axis = read_file(filename, chart_type)
        X.append(x_axis)
        Y.append(y_axis)
        print(filename + " correl: " + str(correl(x_axis, y_axis)))
    draw_chart(X, Y, chart_type, x_title, y_title)
