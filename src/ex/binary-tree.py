import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: " + sys.argv[0] + " <# of hierarchies>")
        exit(0)
    edges = []
    n = int(sys.argv[1])
    for i in range(2 ** (n - 1) - 1):
        # edge to left
        edges.append((i, i * 2 + 1))
        # edge to right
        edges.append((i, i * 2 + 2))
    filename = "graph/" + str(n) + "-binary.gr"
    f = open(filename, "w")
    for edge in edges:
        line = str(edge[0]) + " " + str(edge[1]) + "\n"
        f.write(line)
