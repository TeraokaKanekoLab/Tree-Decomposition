import sys
from collections import Counter


def read_file(filename):
    c = Counter()
    d = dict()
    f = open(filename, "r")
    lines = f.readlines()
    for line in lines:
        left = int(line.split()[0])
        right = int(line.split()[1])
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
    return c, d


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: python3", sys.argv[0], "<filename>")
        exit()
    c, d = read_file(sys.argv[1])
    # while True:
    #     print("Input node number: ", end='')
    #     nd = int(input())
    #     if nd not in d:
    #         print("node " + str(nd) + " doesn't exist")
    #         continue
    #     print("degree: " + str(c[nd]) + ", neighbor:", end='')
    #     for nb in d[nd]:
    #         print(" " + str(nb), end='')
    #     print()
    for nd in d:
        if c[nd] == 10:
            continue
        print("nd: " + str(nd) + ", degree: " +
              str(len(d[nd])) + ", neighbor:", end='')
        for nb in d[nd]:
            print(" " + str(nb), end='')
        print()
