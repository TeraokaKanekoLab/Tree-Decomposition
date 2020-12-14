import sys
from graphviz import Graph
from collections import Counter


def read_file(filename):
    c = Counter()
    d = dict()
    e = []
    f = open(filename, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        e.append((left, right))
        c.update([left])
        c.update([right])
        if left in d:
            d[left].append(right)
        else:
            d[left] = [right]
        if right in d:
            d[right].append(left)
        else:
            d[right] = [left]
    return c, d, e


def hop(c, d, e):
    start = e[0][0]
    nbrs = d[start]
    edges = []
    drawn = dict()
    for nbr in nbrs:
        if start < nbr and not (start, nbr) in drawn:
            edges.append((start, nbr))
            drawn[(start, nbr)] = True
        for nbr2 in d[nbr]:
            if nbr < nbr2 and not (nbr, nbr2) in drawn:
                edges.append((nbr, nbr2))
                drawn[(nbr, nbr2)] = True
            # for nbr3 in d[nbr2]:
            #     if nbr2 < nbr3 and not (nbr2, nbr3) in drawn:
            #         edges.append((nbr2, nbr3))
            #         drawn[(nbr2, nbr3)] = True
    G = Graph(format="pdf")
    G.attr("node", shape="circle")
    filepath = "graph/figures/" + sys.argv[2]
    print(filepath + ".pdf")
    for i, j in edges:
        G.edge(str(i), str(j))
    G.render(filepath)


def full(e):
    G = Graph(format="pdf")
    G.attr("node", shape="circle")
    filepath = "graph/figures/" + sys.argv[2]
    print(filepath + ".pdf")
    for i, j in e:
        G.edge(str(i), str(j))
    G.render(filepath)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<hop or full> <filename>")
        exit()
    c, d, e = read_file("graph/" + sys.argv[2] + ".gr")
    if sys.argv[1] == 'hop':
        hop(c, d, e)
    elif sys.argv[1] == 'full':
        full(e)
    else:
        print("usage: python3", sys.argv[0], "<hop or full> <filename>")
