mdh() {
    echo "g++ src/mdh.cpp -o ./mdh --std=c++17"
    g++ src/mdh.cpp -o ./mdh --std=c++17
    echo "./mdh $1 $2"
    ./mdh $1 $2
    rm ./mdh
}

tree() {
    echo "python3 src/evaluate/tree.py $2 $3"
    python3 src/evaluate/tree.py $2 $3
    filename="tree/figures/"$3"-"$2".pdf"
    open $filename
}

graph() {
    echo "python3 src/evaluate/graph_draw.py $1 $2"
    python3 src/evaluate/graph_draw.py $1 $2
    filename="graph/figures/"$2".pdf"
    open $filename
}

read_tree() {
    echo "python3 src/evaluate/read_tree.py $1 $2"
    python3 src/evaluate/read_tree.py $1 $2
    filename="charts/tree-graph/"$2"-"$1".pdf"
    open $filename
}

dist_root() {
    echo "python3 src/evaluate/dist_root.py $1 $2"
    python3 src/evaluate/dist_root.py $1 $2
    filename="charts/dist_root/"$2"-"$1".pdf"
    open $filename
}

dist_leaf() {
    echo "python3 src/evaluate/dist_leaf.py $1 $2"
    python3 src/evaluate/dist_leaf.py $1 $2
    filename="charts/dist_leaf/"$2"-"$1".pdf"
    open $filename
}

case $1 in
"mdh")
    mdh $2 $3
    tree mdh $2 $3
    ;;
"tree")
    tree $2 $3 $4
    ;;
"graph")
    graph $2 $3
    ;;
"read_tree")
    read_tree $2 $3
    ;;
"dist_root")
    dist_root $2 $3
    ;;
"dist_leaf")
    dist_leaf $2 $3
    ;;
esac
