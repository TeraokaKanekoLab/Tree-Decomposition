import sys
from graphviz import Graph


def read_file():
    filepath = "tree/" + type + "-"+arg_width+"-"+filename+".tree"
    f = open(filepath, "r")
    lines = f.readlines()
    length = len(lines)
    if lines[0].split()[0] != "core":
        root = int(lines[0])
        root_node = str(root)
        for i in lines[1].split():
            root_node += " " + i
        d[root] = root_node
    edges = []
    for i in range(1, length//3):
        nd = int(lines[i*3])
        node = str(nd)
        for j in lines[i*3 + 1].split():
            node += " " + j
            d[nd] = node
        parent = int(lines[i*3 + 2])
        if parent in d:
            edges.append((d[parent], node))
        else:
            edges.append(("core", node))
    return edges


def draw_tree(edges):
    G = Graph(format="pdf")
    G.attr("node", shape="box")
    filepath = "tree/figures/" + type + "-"+arg_width+"-"+filename
    print(filepath + ".pdf")
    for i, j in edges:
        G.edge(i, j)
    G.render(filepath)


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("usage: python3", sys.argv[0], "<type> <filename> <width>")
        exit()
    d = dict()
    type = sys.argv[1]
    filename = sys.argv[2]
    arg_width = sys.argv[3]
    edges = read_file()
    draw_tree(edges)
