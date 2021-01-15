mdh() {
    echo "g++ src/mdh.cpp -o ./mdh --std=c++17"
    g++ src/mdh.cpp -o ./mdh --std=c++17
    echo "./mdh $1 $2"
    ./mdh $1 $2
    rm ./mdh
}

sbr() {
    echo "g++ src/sbr.cpp -o ./sbr --std=c++17"
    g++ src/sbr.cpp -o ./sbr --std=c++17
    echo "./sbr $1 $2"
    ./sbr $1 $2
    rm ./sbr
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
    echo "python3 src/box_plot.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-child/"$2"-"$1".pdf"
    open $filename
}

bc-eccentricity() {
    echo "g++ src/evaluate/bc-eccentricity.cpp -o ./bc-eccentricity --std=c++17"
    g++ src/evaluate/bc-eccentricity.cpp -o ./bc-eccentricity --std=c++17
    echo "./bc-eccentricity $1 $2"
    ./bc-eccentricity $1 $2
    rm ./bc-eccentricity
}

bc-eccentricity-chart() {
    echo "python3 src/box_plot.py bc-eccentricity $1 $2 eccentricity\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-eccentricity $1 $2 eccentricity\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-eccentricity/"$2"-"$1".pdf"
    open $filename
}

bc-bagsize() {
    echo "g++ src/evaluate/bc-bagsize.cpp -o ./bc-bagsize --std=c++17"
    g++ src/evaluate/bc-bagsize.cpp -o ./bc-bagsize --std=c++17
    echo "./bc-bagsize $1 $2"
    ./bc-bagsize $1 $2
    rm ./bc-bagsize
}

bc-bagsize-chart() {
    echo "python3 src/box_plot.py bc-bagsize $1 $2 bagsize\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-bagsize $1 $2 bagsize\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-bagsize/"$2"-"$1".pdf"
    open $filename
}

bc-width() {
    echo "g++ src/evaluate/bc-width.cpp -o ./bc-width --std=c++17"
    g++ src/evaluate/bc-width.cpp -o ./bc-width --std=c++17
    echo "./bc-width $1 $2"
    ./bc-width $1 $2
    rm ./bc-width
}

bc-width-chart() {
    echo "python3 src/box_plot.py bc-width $1 $2 width\ in\ tree betweenness\ centrality"
    python3 src/box_plot.py bc-width $1 $2 width\ in\ tree betweenness\ centrality
    filename="charts/bc-width/"$2"-"$1".pdf"
    open $filename
}

bc-dist_leaf() {
    echo "g++ src/evaluate/bc-dist_leaf.cpp -o ./bc-dist_leaf --std=c++17"
    g++ src/evaluate/bc-dist_leaf.cpp -o ./bc-dist_leaf --std=c++17
    echo "./bc-dist_leaf $1 $2"
    ./bc-dist_leaf $1 $2
    rm ./bc-dist_leaf
}

bc-dist_leaf-chart() {
    echo "python3 src/box_plot.py bc-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-dist_leaf/"$2"-"$1".pdf"
    open $filename
}

ec-dist_leaf() {
    echo "g++ src/evaluate/ec-dist_leaf.cpp -o ./ec-dist_leaf --std=c++17"
    g++ src/evaluate/ec-dist_leaf.cpp -o ./ec-dist_leaf --std=c++17
    echo "./ec-dist_leaf $1 $2"
    ./ec-dist_leaf $1 $2
    rm ./ec-dist_leaf
}

ec-dist_leaf-chart() {
    echo "python3 src/box_plot.py ec-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree eccentricity\ in\ graph"
    python3 src/box_plot.py ec-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree eccentricity\ in\ graph
    filename="charts/ec-dist_leaf/"$2"-"$1".pdf"
    open $filename
}

bc-subtree() {
    echo "g++ src/evaluate/bc-subtree.cpp -o ./bc-subtree --std=c++17"
    g++ src/evaluate/bc-subtree.cpp -o ./bc-subtree --std=c++17
    echo "./bc-subtree $1 $2"
    ./bc-subtree $1 $2
    rm ./bc-subtree
}

bc-subtree-chart() {
    echo "python3 src/box_plot.py bc-subtree $1 $2 subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-subtree $1 $2 subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-subtree/"$2"-"$1".pdf"
    open $filename
}

bc-induce() {
    echo "g++ src/evaluate/bc-induce.cpp -o ./bc-induce --std=c++17"
    g++ src/evaluate/bc-induce.cpp -o ./bc-induce --std=c++17
    echo "./bc-induce $1 $2"
    ./bc-induce $1 $2
    rm ./bc-induce
}

bc-induce-chart() {
    echo "python3 src/box_plot.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-induce/"$2"-"$1".pdf"
    open $filename
}

bc-mainstream() {
    echo "g++ src/evaluate/bc-mainstream.cpp -o ./bc-mainstream --std=c++17"
    g++ src/evaluate/bc-mainstream.cpp -o ./bc-mainstream --std=c++17
    echo "./bc-mainstream $1 $2"
    ./bc-mainstream $1 $2
    rm ./bc-mainstream
}

bc-mainstream-chart() {
    echo "python3 src/box_plot.py bc-mainstream $1 $2 is\ in\ mainstream betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-mainstream $1 $2 is\ in\ mainstream betweenness\ centrality\ in\ graph
    filename="charts/bc-mainstream/"$2"-"$1".pdf"
    open $filename
}

degree-subtree() {
    echo "g++ src/evaluate/degree-subtree.cpp -o ./degree-subtree --std=c++17"
    g++ src/evaluate/degree-subtree.cpp -o ./degree-subtree --std=c++17
    echo "./degree-subtree $1 $2"
    ./degree-subtree $1 $2
    rm ./degree-subtree
}

degree-subtree-chart() {
    echo "python3 src/box_plot.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph"
    python3 src/box_plot.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph
    filename="charts/degree-subtree/"$2"-"$1".pdf"
    open $filename
}

degree-dist_leaf() {
    echo "g++ src/evaluate/degree-dist_leaf.cpp -o ./degree-dist_leaf --std=c++17"
    g++ src/evaluate/degree-dist_leaf.cpp -o ./degree-dist_leaf --std=c++17
    echo "./degree-dist_leaf $1 $2"
    ./degree-dist_leaf $1 $2
    rm ./degree-dist_leaf
}

degree-dist_leaf-chart() {
    echo "python3 src/box_plot.py degree-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree degree\ in\ graph"
    python3 src/box_plot.py degree-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree degree\ in\ graph
    filename="charts/degree-dist_leaf/"$2"-"$1".pdf"
    open $filename
}

center-dist_leaf() {
    echo "g++ src/evaluate/center-dist_leaf.cpp -o ./center-dist_leaf --std=c++17"
    g++ src/evaluate/center-dist_leaf.cpp -o ./center-dist_leaf --std=c++17
    echo "./center-dist_leaf $1 $2"
    ./center-dist_leaf $1 $2
    rm ./center-dist_leaf
}

center-dist_leaf-chart() {
    echo "python3 src/box_plot.py center-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree average\ distance\ from\ centers\ in\ graph"
    python3 src/box_plot.py center-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree average\ distance\ from\ centers\ in\ graph
    filename="charts/center-dist_leaf/"$2"-"$1".pdf"
    open $filename
}

center-dist_root() {
    echo "g++ src/evaluate/center-dist_root.cpp -o ./center-dist_root --std=c++17"
    g++ src/evaluate/center-dist_root.cpp -o ./center-dist_root --std=c++17
    echo "./center-dist_root $1 $2"
    ./center-dist_root $1 $2
    rm ./center-dist_root
}

center-dist_root-chart() {
    echo "python3 src/box_plot.py center-dist_root $1 $2 distance\ from\ root\ in\ tree average\ distance\ from\ centers\ in\ graph"
    python3 src/box_plot.py center-dist_root $1 $2 distance\ from\ root\ in\ tree average\ distance\ from\ centers\ in\ graph
    filename="charts/center-dist_root/"$2"-"$1".pdf"
    open $filename
}

bc-branch() {
    echo "g++ src/evaluate/bc-branch.cpp -o ./bc-branch --std=c++17"
    g++ src/evaluate/bc-branch.cpp -o ./bc-branch --std=c++17
    echo "./bc-branch $1 $2"
    ./bc-branch $1 $2
    rm ./bc-branch
}

bc-branch-chart() {
    echo "python3 src/box_plot.py bc-branch $1 $2 size\ of\ subtree\ with\ branch\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-branch $1 $2 size\ of\ subtree\ with\ branch\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-branch/"$2"-"$1".pdf"
    open $filename
}

bc-ec() {
    echo "g++ src/evaluate/bc-ec.cpp -o ./bc-ec --std=c++17"
    g++ src/evaluate/bc-ec.cpp -o ./bc-ec --std=c++17
    echo "./bc-ec $1 $2"
    ./bc-ec $1 $2
    rm ./bc-ec
}

bc-ec-chart() {
    echo "python3 src/box_plot.py bc-ec $1 $2 eccentricity\ in\ graph betweenness\ centrality\ in\ graph"
    python3 src/box_plot.py bc-ec $1 $2 eccentricity\ in\ graph betweenness\ centrality\ in\ graph
    filename="charts/bc-ec/"$2"-"$1".pdf"
    open $filename
}

select-top() {
    echo "g++ src/evaluate/select-top.cpp -o ./select-top --std=c++17"
    g++ src/evaluate/select-top.cpp -o ./select-top --std=c++17
    echo "./select-top $1 $2"
    ./select-top $1 $2
    rm ./select-top
}

select-top-chart() {
    echo "python3 src/chart/select-top.py $1 $2"
    python3 src/chart/select-top.py $1 $2
    filename="charts/select-top/"$2"-"$1".pdf"
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

write_data() {
    echo "g++ src/ex/write_data.cpp -o write_data --std=c++17"
    g++ src/ex/write_data.cpp -o write_data --std=c++17
    echo "./write_data $1"
    ./write_data $1
    rm ./write_data
}

case $1 in
"mdh")
    mdh $2 $3
    # tree mdh $2 $3
    ;;
"sbr")
    sbr $2 $3
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
    community-chart $2 $3
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
"bc-eccentricity")
    bc-eccentricity $2 $3
    bc-eccentricity-chart $2 $3
    correl "bc-eccentricity" $2 $3
    ;;
"bc-bagsize")
    bc-bagsize $2 $3
    bc-bagsize-chart $2 $3
    correl "bc-bagsize" $2 $3
    ;;
"bc-width")
    bc-width $2 $3
    bc-width-chart $2 $3
    correl "bc-width" $2 $3
    ;;
"bc-dist_leaf")
    bc-dist_leaf $2 $3
    bc-dist_leaf-chart $2 $3
    correl "bc-dist_leaf" $2 $3
    ;;
"bc-dist_leaf-chart")
    bc-dist_leaf-chart $2 $3
    ;;
"bc-subtree")
    bc-subtree $2 $3
    bc-subtree-chart $2 $3
    correl "bc-subtree" $2 $3
    ;;
"bc-induce")
    bc-induce $2 $3
    bc-induce-chart $2 $3
    correl "bc-induce" $2 $3
    ;;
"bc-mainstream")
    bc-mainstream $2 $3
    bc-mainstream-chart $2 $3
    correl "bc-mainstream" $2 $3
    ;;
"degree-subtree")
    degree-subtree $2 $3
    degree-subtree-chart $2 $3
    correl "degree-subtree" $2 $3
    ;;
"degree-dist_leaf")
    degree-dist_leaf $2 $3
    degree-dist_leaf-chart $2 $3
    correl "degree-dist_leaf" $2 $3
    ;;
"center-dist_leaf")
    center-dist_leaf $2 $3
    center-dist_leaf-chart $2 $3
    correl "center-dist_leaf" $2 $3
    ;;
"center-dist_root")
    center-dist_root $2 $3
    center-dist_root-chart $2 $3
    correl "center-dist_root" $2 $3
    ;;
"bc-branch")
    bc-branch $2 $3
    bc-branch-chart $2 $3
    correl "bc-branch" $2 $3
    ;;
"bc-ec")
    bc-ec $2 $3
    bc-ec-chart $2 $3
    correl "bc-ec" $2 $3
    ;;
"ec-dist_leaf")
    ec-dist_leaf $2 $3
    ec-dist_leaf-chart $2 $3
    correl "ec-dist_leaf" $2 $3
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
"write_data")
    write_data $2
    ;;
"select-top")
    select-top $2 $3
    select-top-chart $2 $3
    ;;
"all")
    bc-child $2 $3
    bc-child-chart $2 $3
    bc-eccentricity $2 $3
    bc-eccentricity-chart $2 $3
    bc-bagsize $2 $3
    bc-bagsize-chart $2 $3
    bc-width $2 $3
    bc-width-chart $2 $3
    bc-dist_leaf $2 $3
    bc-dist_leaf-chart $2 $3
    bc-subtree $2 $3
    bc-subtree-chart $2 $3
    bc-induce $2 $3
    bc-induce-chart $2 $3
    bc-mainstream $2 $3
    bc-mainstream-chart $2 $3
    degree-subtree $2 $3
    degree-subtree-chart $2 $3
    degree-dist_leaf $2 $3
    degree-dist_leaf-chart $2 $3
    center-dist_leaf $2 $3
    center-dist_leaf-chart $2 $3
    center-dist_root $2 $3
    center-dist_root-chart $2 $3
    bc-branch $2 $3
    bc-branch-chart $2 $3
    bc-ec $2 $3
    bc-ec-chart $2 $3
    ec-dist_leaf $2 $3
    ec-dist_leaf-chart $2 $3
    ;;
esac
