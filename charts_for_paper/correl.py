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
    for m in METRICS:
        for g in GRAPHS:
            metric = BC + "-" + m
            X, Y, Z, W = read_file(metric, g)
            if g == "ca-grqc-connected":
                print(NAME[m] + " & " + GNAME[g] + " & " + str(round(correl(X, Y), 3)) + " & " +
                      str(round(correl(X, Z), 3)) + " & " + str(round(correl(X, W), 3)) + " \\\\")
            else:
                print(" & " + GNAME[g] + " & " + str(round(correl(X, Y), 3)) + " & " +
                      str(round(correl(X, Z), 3)) + " & " + str(round(correl(X, W), 3)) + " \\\\")
        print("\hline")
