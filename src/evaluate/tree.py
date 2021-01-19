import sys
from graphviz import Graph


# def read_file():
#     filepath = "tree/" + arg_width+"-"+filename+".tree"
#     f = open(filepath, "r")
#     lines = f.readlines()
#     length = len(lines)
#     if lines[0].split()[0] != "core":
#         root = int(lines[0])
#         root_node = str(root)
#         for i in lines[1].split():
#             root_node += " " + i
#         d[root] = root_node
#     edges = []
#     for i in range(1, length//3):
#         nd = int(lines[i*3])
#         node = str(nd)
#         for j in lines[i*3 + 1].split():
#             node += " " + j
#             d[nd] = node
#         parent = int(lines[i*3 + 2])
#         if parent in d:
#             edges.append((d[parent], node))
#         else:
#             edges.append(("core", node))
#     return edges


# def draw_tree(edges):
#     G = Graph(format="pdf")
#     G.attr("node", shape="box")
#     filepath = "tree/figures/" + arg_width+"-"+filename
#     print(filepath + ".pdf")
#     for i, j in edges:
#         G.edge(i, j)
#     G.render(filepath)


# if __name__ == '__main__':
#     if len(sys.argv) != 3:
#         print("usage: python3", sys.argv[0], "<filename> <width>")
#         exit()
#     d = dict()
#     filename = sys.argv[1]
#     arg_width = sys.argv[2]
#     edges = read_file()
#     draw_tree(edges)

import sys
from graphviz import Graph

pref = dict({1: "北海道",
             2: "青森",
             3:	"岩手",
             4:	"宮城",
             5:	"秋田",
             6:	"山形",
             7:	"福島",
             8:	"茨城",
             9:	"栃木",
             10:	"群馬",
             11:	"埼玉",
             12:	"千葉",
             13:	"東京",
             14:	"神奈川",
             15:	"新潟",
             16:	"富山",
             17:	"石川",
             18:	"福井",
             19:	"山梨",
             20:	"長野",
             21:	"岐阜",
             22:	"静岡",
             23:	"愛知",
             24:	"三重",
             25:	"滋賀",
             26:	"京都",
             27:	"大阪",
             28:	"兵庫",
             29:	"奈良",
             30:	"和歌山",
             31:	"鳥取",
             32:	"島根",
             33:	"岡山",
             34:	"広島",
             35:	"山口",
             36:	"徳島",
             37:	"香川",
             38:	"愛媛",
             39:	"高知",
             40:	"福岡",
             41:	"佐賀",
             42:	"長崎",
             43:	"熊本",
             44:	"大分",
             45:	"宮崎",
             46:	"鹿児島",
             47:	"沖縄"})


def convert_to_pref(index):
    pref_name = ""
    prefs = index.split()
    pref_name = pref[int(prefs[0])]
    for i in range(1, len(prefs)):
        pref_next = pref[int(prefs[i])]
        pref_name += " " + pref_next
    return pref_name


def read_file():
    filepath = "tree/" + arg_width+"-"+filename+".tree"
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
    G.attr("node", shape="box", fontname="Hiragino Sans")
    filepath = "tree/figures/" + arg_width+"-"+filename
    print(filepath + ".pdf")
    for i, j in edges:
        G.edge(convert_to_pref(i), convert_to_pref(j))
    G.render(filepath)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("usage: python3", sys.argv[0], "<filename> <width>")
        exit()
    d = dict()
    filename = sys.argv[1]
    arg_width = sys.argv[2]
    edges = read_file()
    draw_tree(edges)
