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
    echo "python3 src/scatter.py community $1 $2 community\ size subtree\ size"
    python3 src/scatter.py community $1 $2 community\ size subtree\ size
    filename="charts/community/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/scatter.py connection $1 $2 connection\ in\ graph connection\ in\ tree"
    python3 src/scatter.py connection $1 $2 connection\ in\ graph connection\ in\ tree
    filename="charts/connection/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph
    echo "python3 src/scatter.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/scatter.py bc-child $1 $2 \#\ of\ children\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-child/box-"$2"-"$1".pdf"
    open $filename
    filename="charts/bc-child/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-eccentricity $1 $2 eccentricity\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-eccentricity $1 $2 eccentricity\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-eccentricity/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-bagsize $1 $2 bagsize\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-bagsize $1 $2 bagsize\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-bagsize/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-width $1 $2 width\ in\ tree betweenness\ centrality"
    python3 src/box.py bc-width $1 $2 width\ in\ tree betweenness\ centrality
    filename="charts/bc-width/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py bc-width $1 $2 width\ in\ tree betweenness\ centrality"
    python3 src/scatter.py bc-width $1 $2 width\ in\ tree betweenness\ centrality
    filename="charts/bc-width/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-dist_leaf/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py ec-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree eccentricity\ in\ graph"
    python3 src/box.py ec-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree eccentricity\ in\ graph
    filename="charts/ec-dist_leaf/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-subtree $1 $2 subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-subtree $1 $2 subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-subtree/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-induce/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/scatter.py bc-induce $1 $2 induced\ subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-induce/scatter-"$2"-"$1".pdf"
    open $filename
}

bc-strahler() {
    echo "g++ src/evaluate/bc-strahler.cpp -o ./bc-strahler --std=c++17"
    g++ src/evaluate/bc-strahler.cpp -o ./bc-strahler --std=c++17
    echo "./bc-strahler $1 $2"
    ./bc-strahler $1 $2
    rm ./bc-strahler
}

bc-strahler-chart() {
    echo "python3 src/box.py bc-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph
    filename="charts/bc-strahler/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py bc-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph"
    python3 src/scatter.py bc-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph
    filename="charts/bc-strahler/scatter-"$2"-"$1".pdf"
    open $filename
}

bc-sum_strahler() {
    echo "g++ src/evaluate/bc-sum_strahler.cpp -o ./bc-sum_strahler --std=c++17"
    g++ src/evaluate/bc-sum_strahler.cpp -o ./bc-sum_strahler --std=c++17
    echo "./bc-sum_strahler $1 $2"
    ./bc-sum_strahler $1 $2
    rm ./bc-sum_strahler
}

bc-sum_strahler-chart() {
    echo "python3 src/box.py bc-sum_strahler $1 $2 sum\ of\ children\ strahler\ number betweenness\ centrality"
    python3 src/box.py bc-sum_strahler $1 $2 sum\ of\ children\ strahler\ number betweenness\ centrality
    filename="charts/bc-sum_strahler/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py bc-sum_strahler $1 $2 sum\ of\ children\ strahler\ number betweenness\ centrality"
    python3 src/scatter.py bc-sum_strahler $1 $2 sum\ of\ children\ strahler\ number betweenness\ centrality
    filename="charts/bc-sum_strahler/scatter-"$2"-"$1".pdf"
    open $filename
}

induce-strahler() {
    echo "g++ src/evaluate/induce-strahler.cpp -o ./induce-strahler --std=c++17"
    g++ src/evaluate/induce-strahler.cpp -o ./induce-strahler --std=c++17
    echo "./induce-strahler $1 $2"
    ./induce-strahler $1 $2
    rm ./induce-strahler
}

induce-strahler-chart() {
    echo "python3 src/box.py induce-strahler $1 $2 strahler\ number ISS"
    python3 src/box.py induce-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph
    filename="charts/induce-strahler/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py induce-strahler $1 $2 strahler\ number ISS"
    python3 src/scatter.py induce-strahler $1 $2 strahler\ number betweenness\ centrality\ in\ graph
    filename="charts/induce-strahler/scatter-"$2"-"$1".pdf"
    open $filename
}

cc-induce() {
    echo "g++ src/evaluate/cc-induce.cpp -o ./cc-induce --std=c++17"
    g++ src/evaluate/cc-induce.cpp -o ./cc-induce --std=c++17
    echo "./cc-induce $1 $2"
    ./cc-induce $1 $2
    rm ./cc-induce
}

cc-induce-chart() {
    echo "python3 src/scatter.py cc-induce $1 $2 induced\ subtree\ size clustering\ coefficient\ in\ graph"
    python3 src/scatter.py cc-induce $1 $2 induced\ subtree\ size clustering\ coefficient\ in\ graph
    filename="charts/cc-induce/scatter-"$2"-"$1".pdf"
    open $filename
}

cc-induce_degree() {
    echo "g++ src/evaluate/cc-induce_degree.cpp -o ./cc-induce_degree --std=c++17"
    g++ src/evaluate/cc-induce_degree.cpp -o ./cc-induce_degree --std=c++17
    echo "./cc-induce_degree $1 $2"
    ./cc-induce_degree $1 $2
    rm ./cc-induce_degree
}

cc-induce_degree-chart() {
    echo "python3 src/scatter.py cc-induce_degree $1 $2 ISS\ -\ degree clustering\ coefficient\ in\ graph"
    python3 src/scatter.py cc-induce_degree $1 $2 ISS\ -\ degree clustering\ coefficient\ in\ graph
    filename="charts/cc-induce_degree/scatter-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/box.py cc-induce_degree $1 $2 ISS\ -\ degree clustering\ coefficient\ in\ graph"
    python3 src/box.py cc-induce_degree $1 $2 ISS\ -\ degree clustering\ coefficient\ in\ graph
    filename="charts/cc-induce_degree/box-"$2"-"$1".pdf"
    open $filename
}

bc-cc() {
    echo "g++ src/evaluate/bc-cc.cpp -o ./bc-cc --std=c++17"
    g++ src/evaluate/bc-cc.cpp -o ./bc-cc --std=c++17
    echo "./bc-cc $1 $2"
    ./bc-cc $1 $2
    rm ./bc-cc
}

bc-cc-chart() {
    echo "python3 src/scatter.py bc-cc $1 $2 clustering\ coefficient\ in\ graph betweenness\ centrality"
    python3 src/scatter.py bc-cc $1 $2 clustering\ coefficient\ in\ graph betweenness\ centrality
    filename="charts/bc-cc/scatter-"$2"-"$1".pdf"
    open $filename
}

bc-total_induce() {
    echo "g++ src/evaluate/bc-total_induce.cpp -o ./bc-total_induce --std=c++17"
    g++ src/evaluate/bc-total_induce.cpp -o ./bc-total_induce --std=c++17
    echo "./bc-total_induce $1 $2"
    ./bc-total_induce $1 $2
    rm ./bc-total_induce
}

bc-total_induce-chart() {
    echo "python3 src/scatter.py bc-total_induce $1 $2 total_induced\ subtree\ size betweenness\ centrality\ in\ graph"
    python3 src/scatter.py bc-total_induce $1 $2 total_induced\ subtree\ size betweenness\ centrality\ in\ graph
    filename="charts/bc-total_induce/scatter-"$2"-"$1".pdf"
    open $filename
}

induce-total_induce() {
    echo "g++ src/evaluate/induce-total_induce.cpp -o ./induce-total_induce --std=c++17"
    g++ src/evaluate/induce-total_induce.cpp -o ./induce-total_induce --std=c++17
    echo "./induce-total_induce $1 $2"
    ./induce-total_induce $1 $2
    rm ./induce-total_induce
}

induce-total_induce-chart() {
    echo "python3 src/scatter.py induce-total_induce $1 $2 induced\ subtree\ size total_induced\ subtree\ size"
    python3 src/scatter.py induce-total_induce $1 $2 induced\ subtree\ size total_induced\ subtree\ size
    filename="charts/induce-total_induce/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-mainstream $1 $2 is\ in\ mainstream betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-mainstream $1 $2 is\ in\ mainstream betweenness\ centrality\ in\ graph
    filename="charts/bc-mainstream/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph"
    python3 src/box.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph
    filename="charts/degree-subtree/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph"
    python3 src/scatter.py degree-subtree $1 $2 subtree\ size\ in\ tree degree\ in\ graph
    filename="charts/degree-subtree/scatter-"$2"-"$1".pdf"
    open $filename
}

degree-induce() {
    echo "g++ src/evaluate/degree-induce.cpp -o ./degree-induce --std=c++17"
    g++ src/evaluate/degree-induce.cpp -o ./degree-induce --std=c++17
    echo "./degree-induce $1 $2"
    ./degree-induce $1 $2
    rm ./degree-induce
}

degree-induce-chart() {
    echo "python3 src/box.py degree-induce $1 $2 induced\ subtree\ size\ in\ tree degree\ in\ graph"
    python3 src/box.py degree-induce $1 $2 induced\ subtree\ size\ in\ tree degree\ in\ graph
    filename="charts/degree-induce/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py degree-induce $1 $2 induced\ subtree\ size\ in\ tree degree\ in\ graph"
    python3 src/scatter.py degree-induce $1 $2 induced\ subtree\ size\ in\ tree degree\ in\ graph
    filename="charts/degree-induce/scatter-"$2"-"$1".pdf"
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
    echo "python3 src/box.py degree-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree degree\ in\ graph"
    python3 src/box.py degree-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree degree\ in\ graph
    filename="charts/degree-dist_leaf/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py center-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree average\ distance\ from\ centers\ in\ graph"
    python3 src/box.py center-dist_leaf $1 $2 distance\ from\ furthest\ descendant\ in\ tree average\ distance\ from\ centers\ in\ graph
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
    echo "python3 src/box.py center-dist_root $1 $2 distance\ from\ root\ in\ tree average\ distance\ from\ centers\ in\ graph"
    python3 src/box.py center-dist_root $1 $2 distance\ from\ root\ in\ tree average\ distance\ from\ centers\ in\ graph
    filename="charts/center-dist_root/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-branch $1 $2 size\ of\ subtree\ with\ branch\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-branch $1 $2 size\ of\ subtree\ with\ branch\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-branch/box-"$2"-"$1".pdf"
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
    echo "python3 src/box.py bc-ec $1 $2 eccentricity\ in\ graph betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-ec $1 $2 eccentricity\ in\ graph betweenness\ centrality\ in\ graph
    filename="charts/bc-ec/box-"$2"-"$1".pdf"
    open $filename
}

bc-degree() {
    echo "g++ src/evaluate/bc-degree.cpp -o ./bc-degree --std=c++17"
    g++ src/evaluate/bc-degree.cpp -o ./bc-degree --std=c++17
    echo "./bc-degree $1 $2"
    ./bc-degree $1 $2
    rm ./bc-degree
}

bc-degree-chart() {
    filename="charts/bc-degree/box-"$2"-"$1".pdf"
    rm $filename
    echo "python3 src/box.py bc-degree $1 $2 degree\ in\ graph betweenness\ centrality"
    python3 src/box.py bc-degree $1 $2 degree\ in\ graph betweenness\ centrality
    open $filename
    filename="charts/bc-degree/scatter-"$2"-"$1".pdf"
    rm $filename
    echo "python3 src/scatter.py bc-degree $1 $2 degree\ in\ graph betweenness\ centrality"
    python3 src/scatter.py bc-degree $1 $2 degree\ in\ graph betweenness\ centrality
    open $filename
}

bc-bc_tree() {
    echo "g++ src/evaluate/bc-bc_tree.cpp -o ./bc-bc_tree --std=c++17"
    g++ src/evaluate/bc-bc_tree.cpp -o ./bc-bc_tree --std=c++17
    echo "./bc-bc_tree $1 $2"
    ./bc-bc_tree $1 $2
    rm ./bc-bc_tree
}

bc-bc_tree-chart() {
    echo "python3 src/box.py bc-bc_tree $1 $2 bc_tree\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/box.py bc-bc_tree $1 $2 bc_tree\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-bc_tree/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py bc-bc_tree $1 $2 bc_tree\ in\ tree betweenness\ centrality\ in\ graph"
    python3 src/scatter.py bc-bc_tree $1 $2 bc_tree\ in\ tree betweenness\ centrality\ in\ graph
    filename="charts/bc-bc_tree/scatter-"$2"-"$1".pdf"
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

select-topk() {
    echo "g++ src/evaluate/select-topk.cpp -o ./select-topk --std=c++17"
    g++ src/evaluate/select-topk.cpp -o ./select-topk --std=c++17
    echo "./select-topk $1 $2"
    ./select-topk $1 $2
    rm ./select-topk
}

select-topk-chart() {
    echo "python3 src/chart/select-topk.py $1 $2"
    python3 src/chart/select-topk.py $1 $2
    filename="charts/select-topk/"$2"-"$1".pdf"
    open $filename
}

induce-degree() {
    echo "g++ src/evaluate/induce-degree.cpp -o ./induce-degree --std=c++17"
    g++ src/evaluate/induce-degree.cpp -o ./induce-degree --std=c++17
    echo "./induce-degree $1 $2"
    ./induce-degree $1 $2
    rm ./induce-degree
}

induce-degree-chart() {
    echo "python3 src/box.py induce-degree $1 $2 degree\ in\ graph induced\ subtree\ size"
    python3 src/box.py induce-degree $1 $2 degree\ in\ graph induced\ subtree\ size
    filename="charts/induce-degree/box-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/scatter.py induce-degree $1 $2 degree\ in\ graph induced\ subtree\ size"
    python3 src/scatter.py induce-degree $1 $2 degree\ in\ graph induced\ subtree\ size
    filename="charts/induce-degree/scatter-"$2"-"$1".pdf"
    open $filename
}

child-induce() {
    echo "g++ src/evaluate/child-induce.cpp -o ./child-induce --std=c++17"
    g++ src/evaluate/child-induce.cpp -o ./child-induce --std=c++17
    echo "./child-induce $1 $2"
    ./child-induce $1 $2
    rm ./child-induce
}

child-induce-chart() {
    echo "python3 src/scatter.py child-induce $1 $2 induced\ subtree\ size \#\ of\ children\ in\ graph"
    python3 src/scatter.py child-induce $1 $2 induced\ subtree\ size \#\ of\ children\ in\ graph
    filename="charts/child-induce/scatter-"$2"-"$1".pdf"
    open $filename
}

child-degree() {
    echo "g++ src/evaluate/child-degree.cpp -o ./child-degree --std=c++17"
    g++ src/evaluate/child-degree.cpp -o ./child-degree --std=c++17
    echo "./child-degree $1 $2"
    ./child-degree $1 $2
    rm ./child-degree
}

child-degree-chart() {
    echo "python3 src/scatter.py child-degree $1 $2 degree \#children\ in\ graph"
    python3 src/scatter.py child-degree $1 $2 degree \#children\ in\ graph
    filename="charts/child-degree/scatter-"$2"-"$1".pdf"
    open $filename
    echo "python3 src/box.py child-degree $1 $2 degree \#children\ in\ graph"
    python3 src/box.py child-degree $1 $2 degree \#children\ in\ graph
    filename="charts/child-degree/box-"$2"-"$1".pdf"
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

free() {
    echo "g++ src/ex/free.cpp -o free --std=c++17"
    g++ src/ex/free.cpp -o free --std=c++17
    echo "./free $1 $2"
    ./free $1 $2
    rm ./free
}

analyze() {
    echo "g++ src/ex/analyze.cpp -o analyze --std=c++17"
    g++ src/ex/analyze.cpp -o analyze --std=c++17
    echo "./analyze $1 $2"
    ./analyze $1 $2
    rm ./analyze
}

research() {
    echo "g++ src/ex/research.cpp -o research --std=c++17"
    g++ src/ex/research.cpp -o research --std=c++17
    echo "./research $1"
    ./research $1
    rm ./research
}

nbr-deg() {
    echo "g++ src/evaluate/nbr-deg.cpp -o nbr-deg --std=c++17"
    g++ src/evaluate/nbr-deg.cpp -o nbr-deg --std=c++17
    echo "./nbr-deg $1 $2"
    ./nbr-deg $1 $2
    rm ./nbr-deg
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
"child-bc")
    child-bc $2 $3
    child-bc-chart $2 $3
    correl "child-bc" $2 $3
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
"bc-strahler")
    bc-strahler $2 $3
    bc-strahler-chart $2 $3
    correl "bc-strahler" $2 $3
    ;;
"bc-sum_strahler")
    bc-sum_strahler $2 $3
    bc-sum_strahler-chart $2 $3
    correl "bc-sum_strahler" $2 $3
    ;;
"bc-induce")
    bc-induce $2 $3
    bc-induce-chart $2 $3
    correl "bc-induce" $2 $3
    ;;
"cc-induce")
    cc-induce $2 $3
    cc-induce-chart $2 $3
    correl "cc-induce" $2 $3
    ;;
"cc-induce_degree")
    cc-induce_degree $2 $3
    cc-induce_degree-chart $2 $3
    correl "cc-induce_degree" $2 $3
    ;;
"bc-total_induce")
    bc-total_induce $2 $3
    bc-total_induce-chart $2 $3
    correl "bc-total_induce" $2 $3
    ;;
"induce-total_induce")
    induce-total_induce $2 $3
    induce-total_induce-chart $2 $3
    correl "induce-total_induce" $2 $3
    ;;
"bc-mainstream")
    bc-mainstream $2 $3
    bc-mainstream-chart $2 $3
    correl "bc-mainstream" $2 $3
    ;;
"degree-induce")
    degree-induce $2 $3
    degree-induce-chart $2 $3
    correl "degree-induce" $2 $3
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
"bc-cc")
    bc-cc $2 $3
    bc-cc-chart $2 $3
    correl "bc-cc" $2 $3
    ;;
"bc-degree")
    bc-degree $2 $3
    bc-degree-chart $2 $3
    correl "bc-degree" $2 $3
    ;;
"bc-bc_tree")
    bc-bc_tree $2 $3
    bc-bc_tree-chart $2 $3
    correl "bc-bc_tree" $2 $3
    ;;
"ec-dist_leaf")
    ec-dist_leaf $2 $3
    ec-dist_leaf-chart $2 $3
    correl "ec-dist_leaf" $2 $3
    ;;
"induce-degree")
    induce-degree $2 $3
    induce-degree-chart $2 $3
    correl "induce-degree" $2 $3
    ;;
"induce-strahler")
    induce-strahler $2 $3
    induce-strahler-chart $2 $3
    correl "induce-strahler" $2 $3
    ;;
"child-induce")
    child-induce $2 $3
    child-induce-chart $2 $3
    correl "child-induce" $2 $3
    ;;
"child-degree")
    child-degree $2 $3
    child-degree-chart $2 $3
    correl "child-degree" $2 $3
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
"free")
    free $2 $3
    ;;
"analyze")
    analyze $2 $3
    ;;
"research")
    research $2
    ;;
"nbr-deg")
    nbr-deg $2 $3
    ;;
"write_data")
    write_data $2
    ;;
"select-top")
    select-top $2 $3
    select-top-chart $2 $3
    ;;
"select-top-chart")
    select-top-chart $2 $3
    ;;
"select-topk")
    select-topk $2 $3
    select-topk-chart $2 $3
    ;;
"select-topk-chart")
    select-topk-chart $2 $3
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
