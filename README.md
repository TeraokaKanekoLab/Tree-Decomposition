# Graph Classification with Tree Decomposition
## General
We aim to classify graphs by exploiting the relation between the width and core size of core-tree-decomposition. The concept is well explained in Chap. 5 of [An Experimental Study of the Treewidth of Real-World Graph Data (Extended Version)](https://arxiv.org/pdf/1901.06862.pdf). The final goal is to find out some parameter or feature from such charts as Figure 6 in the paper that describes the characteristics of the grahs.

## Version History
| Version | Date  | Commit | Notes |
| :-----: | :-: | :-: | :-: |
| **0.1** | September 26, 2020 | [9937d5a](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/9937d5a5b84864d6940aa1f04f197c1cc46925f9) | Read graph data and create a correct `std::vector` |
| 0.1.1 | September 26, 2020 | [e4a2749](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/e4a2749e97babef9878898a89a98953fc08d581d) | Updated `README.md` |
| **0.2** | September 27, 2020 | [b820dc5](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/b820dc59d32b19a977b60574ae9c212071448a31) | Cleaned code and started again |
| 0.2.1 | September 27, 2020 | [f0f5563](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/f0f5563b63ae23d8ee8f05ac9e721cc586fef09d) | Read edges and compute num_nodes and num_edges |
| **0.3** | September 27, 2020 | [0d1879e](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/0d1879eec149104f052d95b716501207b946274c) | Completed `strcut graph` |
| **0.4** | October 16, 2020 | [600f395](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/600f395f6bbf65ea4a9f0ea1fc9e4db396ef91ae) | Show width when reducing each node |
| 0.4.1 | October 16, 2020 | [75a7b4d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/75a7b4d5009f667d1a721beff1fa5342cfb5da2f) | Count true # of nodes; confirmed with official data |
| **0.5** | October 16, 2020 | [2de6338](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/2de6338050e060070e3f3355d7205318eea3a9ef) | Compute # of nodes removed and width at the time |
| **0.6** | October 17, 2020 | [76d8af3](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/76d8af3aa179f340d622b98fb04dd0e489d6e29e) | Create output file that python can read |
| **0.7** | October 17, 2020 | [e5d9f3d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/e5d9f3dd3726b9595f88a161da9215519f081d68) | Added a Python file for creating charts |
| **0.8** | October 17, 2020 | [4cb5f4f](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/4cb5f4f64d10a2903ebd50fff60f6fc7e792de58) | **`make` can create a chart from graph file** |
| **0.9** | October 19, 2020 | [941a34d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/941a34df676fe621957d6d0ae4e548fa6fb7a795) | created update_width() and export_info() |
| **0.10** | October 27, 2020 | [61d9881](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/61d9881d9b2124b55412ddb7b273650fde72c0e0) | Decomposition takes max width size |
| **0.11** | October 30, 2020 | [f7a6a00](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/f7a6a0099b11d08ddcce896bc305911829b251f8) | Added src/min-deg-heu_wo_pq.cpp |
| **0.12** | October 30, 2020 | [d42edfa](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/d42edfa96af346a858489401b725d2fd13f42eb8) | src/without_pq.cpp can create a chart |
| **0.13** | October 30, 2020 | [9522597](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/9522597b9bf303308960b1ac36c878afa4d4904a) | computes degree distribution |

## C++ Version
We recommend to use C++ 20 when you run the codes.

## Git Clone to Your Local Machine
```
git clone https://github.com/TeraokaKanekoLab/Tree-Decomposition.git
```

## How to Run the Program
### The Most Simple Way to Use
Let's say we have a graph data called `simple_graph.txt` in directory `graph`, we create a chart just by running the following command.

```
make GRAPH=simple_graph.txt WIDTH=100
```

Check `charts/` directory and we find `simple_graph.pdf`. Make sure that the extension of the graph file is `.txt`.

### Compute without Priority Queue
```
make random GRAPH=simple_graph.txt WIDTH=100
```

### Compute Degree Distribution
```
make deg GRAPH=simple_graph.txt 
```

### Compile and Execute

```
g++ src/min-deg-heu.cpp -o min-deg-heu
./min-deg-heu <graph data file>
```

If you want to try with a simple graph as an example, this might help.

```
g++ src/min-deg-heu.cpp -o min-deg-heu
./min-deg-heu graph/simple_graph.txt
```

### Graph Data File Format
The graph data files need to follow the rule below. `<endpoint n>` needs to be int (edge No.)

```
<endpoint 1> <endpoint 2>
<endpoint 3> <endpoint 4>
.
.
.
```

Let's say there is a graph like this.
![](https://i.ibb.co/g6F8pfv/images-dragged.jpg)

The following data (`graph/simple_graph.txt`) represents this simple graph with 9 nodes and 12 edges, which are <0, 1>, ..., <6, 8>.

```
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
