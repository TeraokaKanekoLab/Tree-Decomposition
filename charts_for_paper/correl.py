import numpy as np

BC = "bc"
METRICS = ["child", "branch", "bagsize", "width", "subtree", "induce", "total_induce",
           "dist_root", "dist_leaf", "strahler", "sum_strahler", "mainstream",  "bc_tree"]

GRAPHS = ["ca-grqc-connected", "ca-astroph-connected",
          "email-enron-connected", "soc-slashdot"]


def correl(X, Y):
    return np.corrcoef(X, Y)[0, 1]


def read_file(metric, graphname):
    filepath = "output/" + metric + "/1000000-" + graphname + ".output"
    f = open(filepath)
    lines = f.readlines()
    X = []
    Y = []
    Z = []
    W = []
    for line in lines:
        x = float(line.split()[0])
        y = float(line.split()[1])
        z = float(line.split()[2])
        w = float(line.split()[3])
        X.append(x)
        Y.append(y)
        Z.append(z)
        W.append(w)
    return X, Y, Z, W


if __name__ == "__main__":
    for g in GRAPHS:
        print("graph", g)
        for m in METRICS:
            metric = BC + "-" + m
            X, Y, Z, W = read_file(metric, g)
            print(m + "; bc: " + str(correl(X, Y)) + ", deg: " +
                  str(correl(X, Z)) + ", ISS: " + str(correl(X, W)))
