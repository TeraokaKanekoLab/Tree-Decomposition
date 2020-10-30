CC = gcc
GRAPH = simple_graph.txt
WIDTH = 2147483647

make:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(GRAPH)) $(WIDTH)
	python3 src/create_chart.py $(addprefix output/,$(GRAPH))

random:
	g++ src/without_pq.cpp -o without_pq --std=c++17
	./without_pq $(addprefix graph/,$(GRAPH)) $(WIDTH)
	python3 src/create_chart.py $(addprefix output/random-,$(GRAPH))