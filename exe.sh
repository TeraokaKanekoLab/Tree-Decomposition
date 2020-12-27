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

width-chart() {
    echo "python3 src/width/removed_nodes.py $1 $2"
    python3 src/width/removed_nodes.py $1 $2
    filename="charts/width/removed_nodes/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/depth.py $1 $2"
    python3 src/width/depth.py $1 $2
    filename="charts/width/depth/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/child.py $1 $2"
    python3 src/width/child.py $1 $2
    filename="charts/width/child/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/leaf.py $1 $2"
    python3 src/width/leaf.py $1 $2
    filename="charts/width/leaf/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/percent.py $1 $2"
    python3 src/width/percent.py $1 $2
    filename="charts/width/percent/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/strahler.py $1 $2"
    python3 src/width/strahler.py $1 $2
    filename="charts/width/strahler/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/time.py $1 $2"
    python3 src/width/time.py $1 $2
    filename="charts/width/time/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/width/depth-bagsize.py $1 $2"
    python3 src/width/depth-bagsize.py $1 $2
    filename="charts/depth-bagsize/"$2"-"$1".pdf"
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

step-mdh() {
    echo "g++ src/step/mdh.cpp -o ./step-mdh --std=c++17"
    g++ src/step/mdh.cpp -o ./step-mdh --std=c++17
    echo "./step-mdh $1 $2"
    ./step-mdh $1 $2
    rm ./step-mdh
}

step-sbr() {
    echo "g++ src/step/sbr.cpp -o ./sbr --std=c++17"
    g++ src/step/sbr.cpp -o ./step-sbr --std=c++17
    echo "./step-sbr $1 $2"
    ./step-sbr $1 $2
    rm ./step-sbr
}

step-lmdh() {
    echo "g++ src/step/lmdh.cpp -o ./step-lmdh --std=c++17"
    g++ src/step/lmdh.cpp -o ./step-lmdh --std=c++17
    echo "./step-lmdh $1 $2"
    ./step-lmdh $1 $2
    rm ./step-lmdh
}

step-dmdh() {
    echo "g++ src/step/dmdh.cpp -o ./dmdh --std=c++17"
    g++ src/step/dmdh.cpp -o ./step-dmdh --std=c++17
    echo "./step-dmdh $1 $2"
    ./step-dmdh $1 $2
    rm ./step-dmdh
}

step-chart() {
    echo "python3 src/step/depth.py $1 $2"
    python3 src/step/depth.py $1 $2
    filename="charts/step/depth/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/step/child.py $1 $2"
    python3 src/step/child.py $1 $2
    filename="charts/step/child/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/step/leaf.py $1 $2"
    python3 src/step/leaf.py $1 $2
    filename="charts/step/leaf/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/step/strahler.py $1 $2"
    python3 src/step/strahler.py $1 $2
    filename="charts/step/strahler/"$2"-"$1".pdf"
    open $filename
}

start-lmdh() {
    echo "g++ src/start/lmdh.cpp -o ./start-lmdh --std=c++17"
    g++ src/start/lmdh.cpp -o ./start-lmdh --std=c++17
    echo "./start-lmdh $1 $2"
    ./start-lmdh $1 $2
    rm ./start-lmdh
}

start-dmdh() {
    echo "g++ src/start/dmdh.cpp -o ./start-dmdh --std=c++17"
    g++ src/start/dmdh.cpp -o ./start-dmdh --std=c++17
    echo "./start-dmdh $1 $2"
    ./start-dmdh $1 $2
    rm ./start-dmdh
}

start-chart() {
    echo "python3 src/start/depth.py $1 $2"
    python3 src/start/depth.py $1 $2
    filename="charts/start/depth/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/rem-depth.py $1 $2"
    python3 src/start/rem-depth.py $1 $2
    filename="charts/start/rem-depth/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/child.py $1 $2"
    python3 src/start/child.py $1 $2
    filename="charts/start/child/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/leaf.py $1 $2"
    python3 src/start/leaf.py $1 $2
    filename="charts/start/leaf/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/strahler.py $1 $2"
    python3 src/start/strahler.py $1 $2
    filename="charts/start/strahler/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/time.py $1 $2"
    python3 src/start/time.py $1 $2
    filename="charts/start/time/"$2"-"$1".pdf"
    open $filename
    echo "python3 src/start/removed_nodes.py $1 $2"
    python3 src/start/removed_nodes.py $1 $2
    filename="charts/start/removed_nodes/"$2"-"$1".pdf"
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
"width-chart")
    width-chart $2 $3
    ;;
"tree")
    tree $2 $3 $4
    ;;
"graph")
    graph $2 $3
    ;;
"step-mdh")
    step-mdh $2 $3
    ;;
"step-sbr")
    step-sbr $2 $3
    ;;
"step-lmdh")
    step-lmdh $2 $3
    ;;
"step-dmdh")
    step-dmdh $2 $3
    ;;
"step-chart")
    step-chart $2 $3
    ;;
"start-lmdh")
    start-lmdh $2 $3
    ;;
"start-dmdh")
    start-dmdh $2 $3
    ;;
"start-chart")
    start-chart $2 $3
    ;;
"width")
    mdh $2 $3
    sbr $2 $3
    dmdh $2 $3
    lmdh $2 $3
    width-chart $2 $3
    ;;
"step")
    step-mdh $2 $3
    step-sbr $2 $3
    step-dmdh $2 $3
    step-lmdh $2 $3
    step-chart $2 $3
    ;;
"start")
    start-dmdh $2 $3
    start-lmdh $2 $3
    start-chart $2 $3
    ;;
esac
