import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename>", "<width>")
        exit()

    filepath = sys.argv[1]
    f = open(filepath, "r")
    idx = filepath.find("degwidth/")
    path = filepath[:idx]
    filename = filepath[idx + 9:filepath.find(".txt")]
    lines = f.readlines()
    width = int(sys.argv[2])
    nparray = np.zeros((width+1, width+1), dtype=int)
    for line in lines:
        deg, width = map(int, line.split())
        nparray[deg][width] += 1
    print(nparray)
    return nparray, path, filename


def draw_chart(nparray, path, filename):
    sns.set_theme(style="ticks")

    # Load the planets dataset and initialize the figure
    df = pd.DataFrame(nparray)
    g = sns.JointGrid(data=df, x="deg",
                      y="width", marginal_ticks=True)

    # Set a log scaling on the y axis
    g.ax_joint.set(yscale="log")

    # Create an inset legend for the histogram colorbar
    cax = g.fig.add_axes([.15, .55, .02, .2])

    # Add the joint and marginal histogram plots
    g.plot_joint(
        sns.histplot, discrete=(True, False),
        cmap="light:#03012d", pmax=.8, cbar=True, cbar_ax=cax
    )
    g.plot_marginals(sns.histplot, element="step", color="#03012d")
    saved_name = path + "degwidth/charts/" + filename + ".pdf"
    print(saved_name)
    plt.savefig(saved_name)


if __name__ == '__main__':
    nparray, path, filename = read_file()
    draw_chart(nparray, path, filename)
