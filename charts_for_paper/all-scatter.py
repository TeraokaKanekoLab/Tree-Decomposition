import matplotlib.pyplot as plt
import numpy as np

MET_Y = ["bc", "degree", "induce"]
M_NAME = {"bc": "betweenness centrality", "degree": "degree", "induce": "ISS"}

METRICS = ["child", "branch", "bagsize", "width", "subtree", "induce", "total_induce",
           "dist_root", "dist_leaf", "strahler", "sum_strahler", "mainstream",  "bc_tree"]
NAME = {"child": "$CH$", "branch": "$BR$", "bagsize": "$BS$", "width": "$w$", "subtree": "$ST$", "induce": "$ISS$", "total_induce": "$TIS$",
        "dist_root": "$DR$", "dist_leaf": "$DD$", "strahler": "$STR$", "sum_strahler": "$SSTR$", "mainstream": "$TRK$",  "bc_tree": "$TBC$"}

GRAPHS = ["ca-grqc-connected", "ca-astroph-connected",
          "email-enron-connected", "soc-slashdot"]
GNAME = {"ca-grqc-connected": "ca-GrQc", "ca-astroph-connected": "ca-AstroPh",
         "email-enron-connected": "email-Enron", "soc-slashdot": "soc-Slashdot"}


def read_file(filename, chart_type):
    filepath = "output/" + chart_type + "/1000000-" + filename + ".output"
    f = open(filepath, "r")
    lines = f.readlines()
    x1 = []
    y1 = []
    x2 = []
    y2 = []
    x3 = []
    y3 = []
    x4 = []
    y4 = []
    s1 = set()
    s2 = set()
    s3 = set()
    s4 = set()
    for line in lines:
        x = float(line.split()[0])
        y = float(line.split()[1])
        z = float(line.split()[2])
        w = float(line.split()[3])
        v = float(line.split()[4])
        if (x, y) not in s1:
            x1.append(x)
            y1.append(y)
            s1.add((x, y))
        if (x, z) not in s2:
            x2.append(x)
            y2.append(z)
            s2.add((x, z))
        if (x, w) not in s3:
            x3.append(x)
            y3.append(w)
            s3.add((x, w))
        if (x, v) not in s4:
            x4.append(x)
            y4.append(w)
            s4.add((x, v))
    return x1, y1, x2, y2, x3, y3, x4, y4


def print_latex(chart_type, caption):
    print("\\begin{figure}[tbp]")
    print("\\begin{center} ")
    print(
        "\\includegraphics[width=13cm]{figs/appendix/" + chart_type + "-scatter.pdf" + "}")
    print("\\caption{" + caption + "} ")
    print("\\end{center}")
    print("\\end{figure}")
    print()


def draw_chart(X, Y, chart_type, x_title, y_title):
    MARKER_SIZE = 10
    MARKER_COLOR = "blue"
    fig, axes = plt.subplots(2, 2, figsize=(16, 12))
    saved_name = "charts_for_paper/charts/" + chart_type + "-scatter.pdf"
    # print(saved_name)
    for i in range(2):
        for j in range(2):
            ax = axes[i, j]
            index = 2*i + j
            ax.set_title(GRAPHS[index])
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
    for m in METRICS:
        x_title = NAME[m]
        X1 = []
        X2 = []
        X3 = []
        X4 = []
        Y1 = []
        Y2 = []
        Y3 = []
        Y4 = []
        for filename in GRAPHS:
            x1, y1, x2, y2, x3, y3, x4, y4 = read_file(filename, "bc-" + m)
            X1.append(x1)
            Y1.append(y1)
            X2.append(x2)
            Y2.append(y2)
            X3.append(x3)
            Y3.append(y3)
            X4.append(x4)
            Y4.append(y4)
        # draw_chart(X1, Y1, "bc-" + m, x_title, "betweenness centrality")
        # draw_chart(X2, Y2, "degree-" + m, x_title, "degree")
        # draw_chart(X3, Y3, "induce-" + m, x_title, "ISS")
        # draw_chart(X4, Y4, "cc-" + m, x_title, "clustering coefficient")
        print_latex("degree-" + m, "各データセットにおける" + "次数と " + NAME[m] + " の相関")
        print_latex("cc-" + m, "各データセットにおける" +
                    "クラスタリング係数 と " + NAME[m] + " の相関")
        print_latex("bc-" + m, "各データセットにおける" + "媒介中心性と " + NAME[m] + " の相関")
        print_latex("induce-" + m, "各データセットにおける" +
                    " $ISS$ と " + NAME[m] + " の相関")
