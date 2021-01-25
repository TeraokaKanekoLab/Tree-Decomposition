import numpy as np
import subprocess

BC = "bc"
METRICS = ["child", "dist_root", "dist_leaf", "branch", "bagsize", "bc_tree", "mainstream",
           "fillin", "strahler", "sum_strahler", "induce", "total_induce", "subtree", "width"]


if __name__ == "__main__":
    for m in METRICS:
        metric = BC + "-" + m
        subprocess.call(['zsh', './exe.sh', metric,
                         'ca-astroph-connected', "1000000"])
