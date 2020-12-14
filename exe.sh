mdh() {
    echo "g++ src/width/mdh.cpp -o ./mdh --std=c++17"
    g++ src/width/mdh.cpp -o ./mdh --std=c++17
    echo "./mdh $1 $2"
    ./mdh $1 $2
    rm ./mdh
}

sbr() {
    echo "g++ src/width/sbr.cpp -o ./sbr --std=c++17"
    g++ src/width/sbr.cpp -o ./sbr --std=c++17
    echo "./sbr $1 $2"
    ./sbr $1 $2
    rm ./sbr
}

dmdh() {
    echo "g++ src/width/dmdh.cpp -o ./dmdh --std=c++17"
    g++ src/width/dmdh.cpp -o ./dmdh --std=c++17
    echo "./dmdh $1 $2"
    ./dmdh $1 $2
    rm ./dmdh
}

lmdh() {
    echo "g++ src/width/lmdh.cpp -o ./lmdh --std=c++17"
    g++ src/width/lmdh.cpp -o ./lmdh --std=c++17
    echo "./lmdh $1 $2"
    ./lmdh $1 $2
    rm ./lmdh
}

chart() {
    echo "python3 src/width/removed_nodes.py $1 $2"
    python3 src/width/removed_nodes.py $1 $2
    filename="charts/removed_nodes/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/depth.py $1 $2"
    python3 src/width/depth.py $1 $2
    filename="charts/depth/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/child.py $1 $2"
    python3 src/width/child.py $1 $2
    filename="charts/child/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/leaf.py $1 $2"
    python3 src/width/leaf.py $1 $2
    filename="charts/leaf/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/percent.py $1 $2"
    python3 src/width/percent.py $1 $2
    filename="charts/percent/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/strahler.py $1 $2"
    python3 src/width/strahler.py $1 $2
    filename="charts/strahler/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/time.py $1 $2"
    python3 src/width/time.py $1 $2
    filename="charts/time/"$2"-"$1".pdf"
    open $filename
}

tree() {
    echo "python3 src/width/removed_nodes.py $1 $2 $3"
    python3 src/width/tree.py $1 $2 $3
    filename="tree/figures/"$1"-"$3"-"$2".pdf"
    open $filename
}

graph() {
    echo "python3 src/width/graph_draw.py $1 $2"
    python3 src/width/graph_draw.py $1 $2
    filename="graph/figures/"$2".pdf"
    open $filename
}

case $1 in
"mdh")
    mdh $2 $3
    # tree mdh $2 $3
    ;;
"sbr")
    sbr $2 $3
    # tree sbr $2 $3
    ;;
"dmdh")
    dmdh $2 $3
    # tree dmdh $2 $3
    ;;
"lmdh")
    lmdh $2 $3
    # tree lmdh $2 $3
    ;;
"chart")
    chart $2 $3
    ;;
"tree")
    tree $2 $3 $4
    ;;
"graph")
    graph $2 $3
    ;;
"all")
    mdh $2 $3
    sbr $2 $3
    dmdh $2 $3
    lmdh $2 $3
    chart $2 $3
    ;;
esac
