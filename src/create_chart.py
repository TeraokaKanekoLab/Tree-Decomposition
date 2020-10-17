import sys
import matplotlib.pyplot as plt


def read_file():
    if len(sys.argv) != 2:
        print("usage: python3", sys.argv[0], "<filename>")
        exit()

    f = open(sys.argv[1], "r")
    lines = f.readlines()
    widths = []
    num_nodes = []
    for line in lines:
        width, num_node = line.split()
        widths.append(width)
        num_nodes.append(num_node)
    return widths, num_nodes


if __name__ == '__main__':
    width_array, num_nodes = read_file()
    print(width_array)
    print(num_nodes)
