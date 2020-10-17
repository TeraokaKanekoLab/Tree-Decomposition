CC = gcc
GRAPH = simple_graph.txt

make:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(GRAPH))
	python3 src/create_chart.py $(addprefix output/,$(GRAPH))
