import numpy as np

BC = "bc"
METRICS = ["child", "dist_root", "dist_leaf", "branch", "bagsize", "bc_tree", "mainstream",
           "fillin", "strahler", "sum_strahler", "induce", "total_induce", "subtree", "width"]


def correl(X, Y):
    return np.corrcoef(X, Y)[0, 1]


def read_file(metric):
    filepath = "output/" + metric + "/1000000-ca-astroph-connected.output"
    f = open(filepath)
    lines = f.readlines()
    X = []
    Y = []
    for line in lines:
        x = float(line.split()[0])
        y = float(line.split()[2])
        X.append(x)
        Y.append(y)
    return X, Y


if __name__ == "__main__":
    for m in METRICS:
        metric = BC + "-" + m
        X, Y = read_file(metric)
        print(m + ": " + str(correl(X, Y)))
