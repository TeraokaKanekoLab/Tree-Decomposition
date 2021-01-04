import sys
from graphviz import Graph

ansi_to_states = {1:	"AL",
                  2:	"AK",
                  4:	"AZ",
                  5:	"AR",
                  6:	"CA",
                  8:	"CO",
                  9:	"CT",
                  10:	"DE",
                  11:	"DC",
                  12:	"FL",
                  13:	"GA",
                  15:	"HI",
                  16:	"ID",
                  17:	"IL",
                  18:	"IN",
                  19:	"IA",
                  20:	"KS",
                  21:	"KY",
                  22:	"LA",
                  23:	"ME",
                  24:	"MD",
                  25:	"MA",
                  26:	"MI",
                  27:	"MN",
                  28:	"MS",
                  29:	"MO",
                  30:	"MT",
                  31:	"NE",
                  32:	"NV",
                  33:	"NH",
                  34:	"NJ",
                  35:	"NM",
                  36:	"NY",
                  37:	"NC",
                  38:	"ND",
                  39:	"OH",
                  40:	"OK",
                  41:	"OR",
                  42:	"PA",
                  44:	"RI",
                  45:	"SC",
                  46:	"SD",
                  47:	"TN",
                  48:	"TX",
                  49:	"UT",
                  50:	"VT",
                  51:	"VA",
                  53:	"WA",
                  54:	"WV",
                  55:	"WI",
                  56:	"WY"}


def convert_to_pref(index):
    pref_name = ""
    prefs = index.split()
    pref_name = ansi_to_states[int(prefs[0])]
    for i in range(1, len(prefs)):
        pref_next = ansi_to_states[int(prefs[i])]
        pref_name += " " + pref_next
    return pref_name


def read_file():
    filepath = "tree/" + type + "-"+arg_width+"-"+filename+".tree"
    f = open(filepath, "r")
    lines = f.readlines()
    length = len(lines)
    if lines[0].split()[0] != "core":
        root = int(lines[0])
        root_node = str(root)
        for i in lines[1].split():
            root_node += " " + i
        d[root] = root_node
    edges = []
    for i in range(1, length//3):
        nd = int(lines[i*3])
        node = str(nd)
        for j in lines[i*3 + 1].split():
            node += " " + j
            d[nd] = node
        parent = int(lines[i*3 + 2])
        if parent in d:
            edges.append((d[parent], node))
        else:
            edges.append(("core", node))
    return edges


def draw_tree(edges):
    G = Graph(format="pdf")
    G.attr("node", shape="box")
    filepath = "tree/figures/" + type + "-"+arg_width+"-"+filename
    print(filepath + ".pdf")
    for i, j in edges:
        G.edge(convert_to_pref(i), convert_to_pref(j))
    G.render(filepath)


if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("usage: python3", sys.argv[0], "<type> <filename> <width>")
        exit()
    d = dict()
    type = sys.argv[1]
    filename = sys.argv[2]
    arg_width = sys.argv[3]
    edges = read_file()
    draw_tree(edges)
