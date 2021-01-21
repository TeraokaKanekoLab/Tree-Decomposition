import networkx as nx
from networkx.algorithms.centrality import betweenness_centrality
import sys
import time
from datetime import datetime


def read_graph():
    filepath = "graph/" + sys.argv[1] + ".gr"
    graph = nx.Graph()
    f = open(filepath, "r")
    lines = f.readlines()
    for line in lines:
        if '#' in line:
            continue
        left = int(line.split()[0])
        right = int(line.split()[1])
        if left == right:
            continue
        graph.add_edge(left, right)
        graph.add_edge(right, left)
    f.close()
    return graph


def write_to_file(bcs):
    saved_name = "data/betweenness_centrality/" + sys.argv[1] + ".bc"
    f = open(saved_name, "w")
    for key in bcs:
        line = str(key) + " " + str(bcs[key]) + "\n"
        f.write(line)
    f.close()


def write_log(filepath, log):
    f = open(filepath, "a")
    f.write(log)
    f.close()


if __name__ == "__main__":
    start_datetime = datetime.today().strftime('%Y-%m-%d-%H:%M:%S')
    filepath = "log/" + start_datetime + ".log"
    msg = "src/evaluate/betweenness_centrality.py " + sys.argv[1] + "\n"
    write_log(filepath, msg)
    print("loading...")
    graph = read_graph()
    print("calculating...")
    start = time.time()
    msg = "program execution started at " + start_datetime + "\n"
    write_log(filepath, msg)
    bcs = betweenness_centrality(graph)
    end = time.time()
    print("writing result...")
    write_to_file(bcs)
    end_datetime = datetime.today().strftime('%Y-%m-%d-%H:%M:%S')
    msg = "program execution ended at " + end_datetime + "\n"
    write_log(filepath, msg)
    msg = "total execution time: " + str(end-start) + "\n"
    write_log(filepath, msg)
