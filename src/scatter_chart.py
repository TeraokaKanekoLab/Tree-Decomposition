import sys
import matplotlib.pyplot as plt


def read_file():
    filepath = "output/" + chart_type + "/" + \
        arg_width + "-" + filename + ".output"
    f = open(filepath, "r")
    lines = f.readlines()
    x_axis = []
    y_axis = []
    for line in lines:
        left = int(line.split()[0])
        right = int(line.split()[1])
        x_axis.append(left)
        y_axis.append(right)
    return x_axis, y_axis


def draw_chart(x_axis, y_axis):
    plt.scatter(x_axis, y_axis, c="r")
    width = sys.argv[2]
    saved_name = "charts/" + chart_type + "/" + arg_width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel(x_axis_title)
    plt.ylabel(y_axis_title)
    plt.title(y_axis_title + " over " + x_axis_title + "; " +
              width + ": " + filename)
    plt.savefig(saved_name)


if __name__ == '__main__':
    if len(sys.argv) != 6:
        print("usage: python3",
              sys.argv[0], "<chart_type> <filename> <width> <x_axis title> <y_axis title>")
        exit()
    chart_type = sys.argv[1]
    filename = sys.argv[2]
    arg_width = sys.argv[3]
    x_axis_title = sys.argv[4]
    y_axis_title = sys.argv[5]

    x_axis, y_axis = read_file()
    draw_chart(x_axis, y_axis)
