import sys
import matplotlib.pyplot as plt


def color_normalize(r, g, b):
    return [[r/256, g/256, b/256]]


RED = color_normalize(219, 68, 55)
GREEN = color_normalize(15, 157, 88)
BLUE = color_normalize(66, 133, 244)
YELLOW = color_normalize(244, 160, 0)
BLACK = color_normalize(59, 59, 59)


def read_file():
    filepath = "output/" + chart_type + "/" + \
        arg_width + "-" + filename + ".output"
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


def draw_chart(x_axis, y_axis):
    fig, ax = plt.subplots(figsize=(8, 6))
    plt.scatter(x_axis, y_axis, c=BLUE)
    saved_name = "charts/" + chart_type + "/scatter-" +\
        arg_width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(left=0)
    plt.ylim(bottom=0)
    plt.xlabel(x_axis_title)
    plt.ylabel(y_axis_title)
    plt.title(y_axis_title + " over " + x_axis_title + ": " + filename)
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
