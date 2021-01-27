import numpy as np
import subprocess

BC = "bc"
METRICS = ["child", "dist_root", "dist_leaf", "branch", "bagsize", "bc_tree", "mainstream",
           "fillin", "strahler", "sum_strahler", "induce", "total_induce", "subtree", "width"]

GRAPHS = ["ca-grqc-connected", "ca-astroph-connected",
          "email-enron-connected", "soc-slashdot"]


if __name__ == "__main__":
    for g in GRAPHS:
        for m in METRICS:
            metric = BC + "-" + m
            subprocess.call(['zsh', './exe.sh', metric, g, "1000000"])
