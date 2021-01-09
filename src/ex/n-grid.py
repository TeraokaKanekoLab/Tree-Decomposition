import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: " + sys.argv[0] + " <n>")
        exit(0)
    edges = []
    n = int(sys.argv[1])
    for i in range(n ** 2):
        # edge to right
        if i % n != n - 1:
            edges.append((i, i + 1))
        # edge to below
        if i // n < n - 1:
            edges.append((i, i + n))
    filename = "graph/" + str(n) + "-grid.gr"
    f = open(filename, "w")
    for edge in edges:
        line = str(edge[0]) + " " + str(edge[1]) + "\n"
        f.write(line)
