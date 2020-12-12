# Graph Classification with Tree Decomposition
## General
We aim to classify graphs by exploiting the relation between the width and core size of core-tree-decomposition. The concept is well explained in Chap. 5 of [An Experimental Study of the Treewidth of Real-World Graph Data (Extended Version)](https://arxiv.org/pdf/1901.06862.pdf). The final goal is to find out some parameter or feature from such charts as Figure 6 in the paper that describes the characteristics of the grahs.

## Version History
| Version | Date  | Commit | Notes |
| :-----: | :-: | :-: | :-: |
| 0.1 | September 26, 2020 | [9937d5a](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/9937d5a5b84864d6940aa1f04f197c1cc46925f9) | Read graph data and create a correct `std::vector` |
| 0.2 | September 27, 2020 | [b820dc5](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/b820dc59d32b19a977b60574ae9c212071448a31) | Cleaned code and started again |
| 0.2.1 | September 27, 2020 | [f0f5563](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/f0f5563b63ae23d8ee8f05ac9e721cc586fef09d) | Read edges and compute num_nodes and num_edges |
| 0.3 | September 27, 2020 | [0d1879e](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/0d1879eec149104f052d95b716501207b946274c) | Completed `strcut graph` |
| 0.4 | October 16, 2020 | [600f395](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/600f395f6bbf65ea4a9f0ea1fc9e4db396ef91ae) | Show width when reducing each node |
| 0.4.1 | October 16, 2020 | [75a7b4d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/75a7b4d5009f667d1a721beff1fa5342cfb5da2f) | Count true # of nodes; confirmed with official data |
| 0.5 | October 16, 2020 | [2de6338](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/2de6338050e060070e3f3355d7205318eea3a9ef) | Compute # of nodes removed and width at the time |
| 0.6 | October 17, 2020 | [76d8af3](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/76d8af3aa179f340d622b98fb04dd0e489d6e29e) | Create output file that python can read |
| 0.7 | October 17, 2020 | [e5d9f3d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/e5d9f3dd3726b9595f88a161da9215519f081d68) | Added a Python file for creating charts |
| 0.8 | October 17, 2020 | [4cb5f4f](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/4cb5f4f64d10a2903ebd50fff60f6fc7e792de58) | `make` can create a chart from graph file |
| 0.9 | October 19, 2020 | [941a34d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/941a34df676fe621957d6d0ae4e548fa6fb7a795) | created update_width() and export_info() |
| 0.10 | October 27, 2020 | [61d9881](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/61d9881d9b2124b55412ddb7b273650fde72c0e0) | Decomposition takes max width size |
| 0.11 | October 30, 2020 | [f7a6a00](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/f7a6a0099b11d08ddcce896bc305911829b251f8) | Added src/min-deg-heu_wo_pq.cpp |
| 0.12 | October 30, 2020 | [d42edfa](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/d42edfa96af346a858489401b725d2fd13f42eb8) | src/without_pq.cpp can create a chart |
| 0.13 | October 30, 2020 | [9522597](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/9522597b9bf303308960b1ac36c878afa4d4904a) | computes degree distribution |
| 0.14 | October 31, 2020 | [1caceaf](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/1caceafaaf56a63007d1362138600e14c4e61993) | creates integrated charts |
| 0.15 | November 3, 2020 | [538f71d](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/538f71d56d87532708dbbc8ac34634b129f77f65) | changed representation: from # of removed nodes to % of removed nodes |
| 0.16 | November 6, 2020 | [5cd58da](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/538f71d56d87532708dbbc8ac34634b129f77f65) | modified filename rules |
| 0.17 | November 8, 2020 | [a6ea20a](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/a6ea20adcb272671e686c4213d24c67f7b480e71) | Added worst case series to integrated chart |
| 0.18 | November 9, 2020 | [6fdee51](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/6fdee514c62f267c4de96281d53c000e49bda94d) | Set interval of plotting |
| 0.19 | November 9, 2020 | [cf56ce7](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/cf56ce7eb259e17e0d12f331d26d6201dc1dae50) | Refactored worst and random |
| 0.20 | November 9, 2020 | [c47f8f2](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/c47f8f29b03b512d7ed8cfe6ffb4163aba7cfb5f) | First version of src/walk.cpp |
| 0.21 | November 21, 2020 | [84cf670](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/84cf670745ac0af40331aeeab2fd6a494d354ed6) | First version of src/walk.cpp |
| **1.0** | December 6, 2020 | [ebdfc13](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/ebdfc1356c2511e8cbc2de0a04f1abbbfaf248b1) | **Theme fixed!** |
| 1.1 | December 10, 2020 | [43fea4b](https://github.com/TeraokaKanekoLab/Tree-Decomposition/commit/43fea4baf85e13764217f3eef46e875cd997bad0) | Implemented strahler number |

## How to Run the Program
```
sh exe.sh all simple_graph 3
```

## C++ Version
We recommend to use C++ 20 when you run the codes.

## Git Clone to Your Local Machine
```
git clone https://github.com/TeraokaKanekoLab/Tree-Decomposition.git
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

The following data (`graph/simple_graph.gr`) represents this simple graph with 9 nodes and 12 edges, which are <0, 1>, ..., <6, 8>.

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
1. Fragkiskos Malliaros, Christos Giatsidis, Apostolos Papadopoulos, Michalis Vazirgiannis. [The Core Decomposition of Networks: Theory, Algorithms and Applications](https://hal-centralesupelec.archives-ouvertes.fr/hal-01986309/file/Core_Decomposition_VLDBJ.pdf). The *VLDB Journal*, Springer, 2019.
1. Silviu Maniu, Pierre Senellart, and Suraj Jog. [An Experimental Study of the Treewidth of Real-World Graph Data](https://drops.dagstuhl.de/opus/volltexte/2019/10314/pdf/LIPIcs-ICDT-2019-12.pdf). In 22nd International Conference on Database Theory, *ICDT* 2019, March 26-28, 2019, Lisbon, Portugal, pages 12:1–12:18, 2019.
1. Takanori Maehara, Takuya Akiba, Yoichi Iwata, and Ken-ichi Kawarabayashi. [Computing personalized pagerank quickly by exploiting graph structures](http://www.vldb.org/pvldb/vol7/p1023-maehara.pdf). Proceedings of the VLDB Endowment, 7(12):1023–1034, 2014.
1. T. Akiba, C. Sommer, and K. Kawarabayashi. [Shortest-path queries for complex networks: exploiting low tree-width outside the core](https://dl.acm.org/doi/pdf/10.1145/2247596.2247614). In *EDBT*, pages 144–155, 2012.
1. A. Berry, P. Heggernes, and G. Simonet. [The minimum degree heuristic and the minimal triangulation process](https://link.springer.com/chapter/10.1007/978-3-540-39890-5_6). In *Graph-Theoretic Concepts in Computer Science*, volume 2880, pages 58–70. 2003.
1. H. L. Bodlaender. [A linear-time algorithm for finding tree-decompositions of small treewidth](https://dl.acm.org/doi/pdf/10.1145/167088.167161). *SIAM J. Comput.*, 25(6):1305–1317, 1996.
1. H. L. Bodlaender. [Treewidth: Characterizations, applications, and computations](https://link.springer.com/chapter/10.1007/11917496_1). In *Graph-Theoretic Concepts in Computer Science*, pages 1–14, 2006.
1. J. Lescovec. [Stanford Large Network Dataset Collection](https://snap.stanford.edu/data).
1. T. Maehara, T. Akiba, Y. Iwata, and K. Kawarabayashi. [Computing personalized pagerank quickly by exploiting graph structures](http://www.vldb.org/pvldb/vol7/p1023-maehara.pdf). *Proceedings of the VLDB Endowment*, 7(12):1023–1034, 2014.
1. D. Ouyang, L. Qin, L. Chang, X. Lin, Y. Zhang, and Q. Zhu. 2018. [When Hierarchy Meets 2-Hop-Labeling: Efficient Shortest Distance Queries on Road Networks](https://dl.acm.org/doi/pdf/10.1145/3183713.3196913). In *Proceedings of the SIGMOD '18*, pages 709–724.2018.
1. R. Rossi, N. Ahmed. [Network Repository. An Interactive Scientific Network Data Repository](http://networkrepository.com).
1. F. Wei. [Tedi: efficient shortest path query answering on graphs](https://dl.acm.org/doi/pdf/10.1145/1807167.1807181). In *SIGMOD*, pages 99–110, 2010.
1. J. Xu, F. Jiao, and B. Berger. [A tree-decomposition approach to protein structure prediction](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=1498026). In *CSB*, pages 247–256, 2005.