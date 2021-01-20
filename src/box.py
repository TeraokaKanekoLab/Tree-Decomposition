import matplotlib.pyplot as plt
import sys
import matplotlib as mpl
mpl.use('agg')

DIV = 10


def divide_in_ten(x_axis, y_axis, x_max, x_min):
    x_max -= x_min
    data_to_plot = []
    x_tick_label = []
    x_max = (x_max // DIV + 1) * DIV
    for i in range(DIV):
        data_to_plot.append([])
        label = str(x_max // DIV * i + x_min) + \
            "-" + str(x_max // DIV * (i + 1) + x_min)
        x_tick_label.append(label)
    for x, y in zip(x_axis, y_axis):
        for i in range(DIV):
            if x < x_max // DIV * (i + 1):
                data_to_plot[i].append(y)
                break
    return data_to_plot, x_tick_label


def read_file():
    filepath = "output/" + chart_type + "/" + \
        arg_width + "-" + filename + ".output"
    f = open(filepath, "r")
    lines = f.readlines()
    pre_x_axis = []
    y_axis = []
    for line in lines:
        left = int(line.split()[0])
        right = float(line.split()[1])
        pre_x_axis.append(left)
        y_axis.append(right)
    x_max = max(pre_x_axis)
    x_min = min(pre_x_axis)
    x_axis = []
    for i in range(len(pre_x_axis)):
        x_axis.append(pre_x_axis[i] - x_min)
    if x_max >= DIV*1.5:
        return divide_in_ten(x_axis, y_axis, x_max, x_min)
    data_to_plot = []
    for i in range(x_min, x_max+1):
        data_to_plot.append([])
    for x, y in zip(x_axis, y_axis):
        data_to_plot[x].append(y)
    return data_to_plot, [str(i) for i in range(x_min, x_max+1)]


def draw_chart(data_to_plot, x_tick_label):
    saved_name = "charts/" + chart_type + "/box-" + \
        arg_width + "-" + filename + ".pdf"
    print(saved_name)
    fig, axes = plt.subplots(figsize=(12, 8))
    # plt.boxplot(data_to_plot, sym='')
    plt.boxplot(data_to_plot)
    axes.set_xticklabels(x_tick_label)
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

    data_to_plot, x_tick_label = read_file()
    draw_chart(data_to_plot, x_tick_label)
