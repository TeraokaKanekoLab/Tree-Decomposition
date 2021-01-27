import numpy as np

BC = "bc"
METRICS = ["child", "branch", "bagsize", "width", "subtree", "induce", "total_induce",
           "dist_root", "dist_leaf", "strahler", "sum_strahler", "mainstream",  "bc_tree"]
NAME = {"child": "$CH$", "branch": "$BR$", "bagsize": "$BS$", "width": "$w$", "subtree": "$ST$", "induce": "$ISS$", "total_induce": "$TIS$",
        "dist_root": "$DR$", "dist_leaf": "$DD$", "strahler": "$STR$", "sum_strahler": "$SSTR$", "mainstream": "$TRK$",  "bc_tree": "$TBC$"}

GRAPHS = ["ca-grqc-connected", "ca-astroph-connected",
          "email-enron-connected", "soc-slashdot"]
GNAME = {"ca-grqc-connected": "ca-GrQc", "ca-astroph-connected": "ca-AstroPh",
         "email-enron-connected": "email-Enron", "soc-slashdot": "soc-Slashdot"}


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
    V = []
    for line in lines:
        x = float(line.split()[0])
        y = float(line.split()[1])
        z = float(line.split()[2])
        w = float(line.split()[3])
        v = float(line.split()[4])
        X.append(x)  # metric
        Y.append(y)  # bc
        Z.append(z)  # degree
        W.append(w)  # iss
        V.append(v)  # cc
    return X, Y, Z, W, V


if __name__ == "__main__":
    for m in METRICS:
        print(NAME[m], end='')
        for g in GRAPHS:
            metric = BC + "-" + m
            X, Y, Z, W, V = read_file(metric, g)
            print(" & " + GNAME[g] + " & " + str(round(correl(X, Z), 3)) + " & " + str(round(correl(X, V), 3)
                                                                                       ) + " & " + str(round(correl(X, Y), 3)) + " & " + str(round(correl(X, W), 3)) + " \\\\")
        print("\hline")
