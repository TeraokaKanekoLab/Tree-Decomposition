mdh() {
    echo "g++ src/mdh.cpp -o ./mdh --std=c++17"
    g++ src/mdh.cpp -o ./mdh --std=c++17
    echo "./mdh $1 $2"
    ./mdh $1 $2
    rm ./mdh
}

tree() {
    echo "python3 src/evaluate/tree.py $1 $2"
    python3 src/evaluate/tree.py $1 $2
    filename="tree/figures/"$2"-"$1".pdf"
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

open-chart() {
    filename="charts/tree-graph/"$2"-"$1".pdf"
    open $filename
    filename="charts/dist_root/"$2"-"$1".pdf"
    open $filename
    filename="charts/dist_leaf/"$2"-"$1".pdf"
    open $filename
}

community() {
    echo "g++ src/evaluate/community.cpp -o ./community --std=c++17"
    g++ src/evaluate/community.cpp -o ./community --std=c++17
    echo "./community $1 $2"
    ./community $1 $2
    rm ./community
}

community-chart() {
    echo "python3 src/scatter_chart.py community $1 $2 community\ size subtree\ size"
    python3 src/scatter_chart.py community $1 $2 community\ size subtree\ size
    filename="charts/community/"$2"-"$1".pdf"
    open $filename
}

connection() {
    echo "g++ src/evaluate/connection.cpp -o ./connection --std=c++17"
    g++ src/evaluate/connection.cpp -o ./connection --std=c++17
    echo "./connection $1 $2"
    ./connection $1 $2
    rm ./connection
}

connection-chart() {
    echo "python3 src/scatter_chart.py connection $1 $2 connection\ in\ graph connection\ in\ tree"
    python3 src/scatter_chart.py connection $1 $2 connection\ in\ graph connection\ in\ tree
    filename="charts/connection/"$2"-"$1".pdf"
    open $filename
}

bc-child() {
    echo "g++ src/evaluate/bc-child.cpp -o ./bc-child --std=c++17"
    g++ src/evaluate/bc-child.cpp -o ./bc-child --std=c++17
    echo "./bc-child $1 $2"
    ./bc-child $1 $2
    rm ./bc-child
}

bc-child-chart() {
    echo "python3 src/scatter_chart.py bc-child $1 $2 \#\ of\ children betweenness\ centrality"
    python3 src/scatter_chart.py bc-child $1 $2 \#\ of\ children betweenness\ centrality
    filename="charts/bc-child/"$2"-"$1".pdf"
    open $filename
}

correl() {
    echo "python3 src/evaluate/correl.py $1 $2 $3"
    python3 src/evaluate/correl.py $1 $2 $3
}

ex() {
    echo "g++ src/ex/ex.cpp -o ex --std=c++17"
    g++ src/ex/ex.cpp -o ex --std=c++17
    echo "./ex $1"
    ./ex $1
    rm ./ex
}

case $1 in
"mdh")
    mdh $2 $3
    # tree mdh $2 $3
    ;;
"tree")
    tree $2 $3
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
"community")
    community $2 $3
    # community-chart $2 $3
    ;;
"community-chart")
    community-chart $2 $3
    ;;
"connection")
    connection $2 $3
    connection-chart $2 $3
    correl "connection" $2 $3
    ;;
"connection-chart")
    connection-chart $2 $3
    correl "connection" $2 $3
    ;;
"bc-child")
    bc-child $2 $3
    bc-child-chart $2 $3
    correl "bc-child" $2 $3
    ;;
"chart")
    community-chart $2 $3
    connection-chart $2 $3
    open-chart $2 $3
    ;;
"correl")
    correl $2 $3 $4
    ;;
"ex")
    ex $2
    ;;
esac
