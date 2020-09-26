# Graph Classification with Tree Decomposition
## General
We aim to classify graphs by exploiting the relation between the width and core size of core-tree-decomposition. The concept is well explained in Chap. 5 of [An Experimental Study of the Treewidth of Real-World Graph Data (Extended Version)](https://arxiv.org/pdf/1901.06862.pdf). The final goal is to find out some parameter or feature from such charts as Figure 6 in the paper that describes the characteristics of the grahs.

## Version History
| Version | Date  | Notes |
| :-----: | :-: | :-: |
| **1.0** | September 26, 2020 | Read graph data and create a correct `std::vector` |


## C++ Version
We recommend to use C++ 20 when you run the codes.

## Git Clone to Your Local Machine
```
git clone https://github.com/TeraokaKanekoLab/Tree-Decomposition.git
```

## How to Run the Program
### Compile and Execute

```
g++ src/min-deg-heu.cpp -o min-deg-heu
./min-deg-heu <graph data file>
```

If you want to try with a simple graph as an example, this might help.

```
g++ src/min-deg-heu.cpp -o min-deg-heu
./min-deg-heu graph/simple_graph
```

### Graph Data File Format
The graph data files need to follow the rule below. `<endpoint n>` needs to be int (edge No.)

```
<# of nodes> <# of edges>
<endpoint 1> <endpoint 2>
<endpoint 3> <endpoint 4>
.
.
.
```

Let's say there is a graph like this.
![](https://i.ibb.co/DtGNpxC/simple-graph.png)

The following data (`graph/simple_graph.txt`) represents this simple graph with 9 nodes and 12 edges, which are <0, 1>, ..., <6, 8>.

```
9 12
0 1
0 2
1 2
1 3
2 3
2 6
3 4
3 5
4 7
5 7
5 8
6 8
```

## References
1. Fragkiskos Malliaros, Christos Giatsidis, Apostolos Papadopoulos, Michalis Vazirgiannis. [The Core Decomposition of Networks: Theory, Algorithms and Applications](https://hal-centralesupelec.archives-ouvertes.fr/hal-01986309/file/Core_Decomposition_VLDBJ.pdf). The VLDB Journal, Springer, 2019. hal-01986309v3
1. Silviu Maniu, Pierre Senellart, and Suraj Jog. [An Experimental Study of the Treewidth of Real-World Graph Data](https://drops.dagstuhl.de/opus/volltexte/2019/10314/pdf/LIPIcs-ICDT-2019-12.pdf). In 22nd International Conference on Database Theory, ICDT 2019, March 26-28, 2019, Lisbon, Portugal, pages 12:1–12:18, 2019.
1. Takanori Maehara, Takuya Akiba, Yoichi Iwata, and Ken-ichi Kawarabayashi. [Computing personalized pagerank quickly by exploiting graph structures](http://www.vldb.org/pvldb/vol7/p1023-maehara.pdf). Proceedings of the VLDB Endowment, 7(12):1023–1034, 2014.