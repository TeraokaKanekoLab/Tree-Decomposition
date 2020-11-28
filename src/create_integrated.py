import sys
import numpy as np
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()

    filepath = sys.argv[1]
    arg_width = sys.argv[2]
    idx = filepath.find("output/")
    path = filepath[:idx]
    filename = filepath[idx + 7:filepath.find(".txt")]
    filepath = "output/"+arg_width+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths1 = []
    num_nodes1 = []
    percentages1 = []
    length = len(lines)
    num_nodes = int(lines[0])
    for i in range(1, length):
        line = lines[i]
        width1 = int(line.split()[0])
        num_node = int(line.split()[1])
        widths1.append(width1)
        num_nodes1.append(num_node)
        percentages1.append(num_node/num_nodes * 100)

    filepath = "output/" + arg_width+"-random"+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths2 = []
    num_nodes2 = []
    percentages2 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths2.append(width)
        num_nodes2.append(num_node)
        percentages2.append(num_node/num_nodes * 100)

    filepath = "output/" + arg_width+"-desce"+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths3 = []
    num_nodes3 = []
    percentages3 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths3.append(width)
        num_nodes3.append(num_node)
        percentages3.append(num_node/num_nodes * 100)

    filepath = "output/" + arg_width+"-asce"+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths4 = []
    num_nodes4 = []
    percentages4 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths4.append(width)
        num_nodes4.append(num_node)
        percentages4.append(num_node/num_nodes * 100)

    filepath = "output/" + arg_width+"-walk"+"-"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths5 = []
    num_nodes5 = []
    percentages5 = []
    for line in lines:
        width, num_node = map(int, line.split())
        widths5.append(width)
        num_nodes5.append(num_node)
        percentages5.append(num_node/num_nodes * 100)

    filepath = "degree/"+filename+".txt"
    f = open(filepath, "r")
    lines = f.readlines()
    widths_deg = []
    num_nodes_deg = []
    percentages_deg = []
    current_ne = 0
    num_edges = int(lines[0])
    length = len(lines)
    for i in range(1, length):
        line = lines[i]
        deg, num_node = map(int, line.split())
        widths_deg.append(deg)
        num_nodes_deg.append(num_node)
        current_ne += num_node
        percentages_deg.append(current_ne/num_nodes * 100)
    return widths1, percentages1, widths2, percentages2, widths3, percentages3, widths4, percentages4, widths5, percentages5, widths_deg, percentages_deg, path, filename


def draw_chart(x_axis1, y_axis1, x_axis2, y_axis2, x_axis3, y_axis3, x_axis4, y_axis4, x_axis5, y_axis5, x_axis6, y_axis6, path, filename):
    plt.plot(x_axis1, y_axis1,  c="b",  label="SBR")
    plt.plot(x_axis2, y_axis2, c="g",  label="random")
    plt.plot(x_axis3, y_axis3, c="r",  label="desce")
    plt.plot(x_axis4, y_axis4, c="c",  label="asce")
    plt.plot(x_axis5, y_axis5, c="m",  label="walk")
    plt.plot(x_axis6, y_axis6, c="k",  label="degree")
    width = sys.argv[2]
    saved_name = path + "charts/integrated-" + width + "-" + filename + ".pdf"
    print(saved_name)
    plt.xlim(0, int(width))
    plt.ylim(0, 100)
    plt.xlabel("width/degree")
    plt.ylabel("% of removed nodes")
    plt.title("% of removed nodes over width: " + filename)
    plt.legend(loc="lower right", fontsize=14)  # (7)凡例表示
    plt.savefig(saved_name)


if __name__ == '__main__':
    widths1, percentages1, widths2, percentages2, widths3, percentages3, widths4, percentages4, widths5, percentages5, widths_deg, percentages_deg, path, filename = read_file()
    draw_chart(widths1, percentages1, widths2, percentages2, widths3, percentages3, widths4,
               percentages4, widths5, percentages5, widths_deg, percentages_deg, path, filename)
