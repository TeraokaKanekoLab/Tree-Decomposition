# Graph Classification with Tree Decomposition
## How to Run the Program
### Compile and Execute

```
g++ src/min-deg-heu.cpp -o min-deg-heu
./min-deg-heu <graph data file>
```

### Graph Data File Format
The graph data files need to follow the rule below. <endpoint n> needs to be int (edge No.)

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