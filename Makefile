CC = gcc
G = simple_graph.txt
W = 2147483647

make:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(G)) $(W)
	g++ src/without_pq.cpp -o without_pq --std=c++17
	./without_pq $(addprefix graph/,$(G)) $(W)
	python3 src/create_integrated_chart.py $(addprefix output/,$(G))

pq:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/,$(G))

random:
	g++ src/without_pq.cpp -o without_pq --std=c++17
	./without_pq $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/random-,$(G))

deg:
	g++ src/count_degree.cpp -o count_degree --std=c++17
	./count_degree $(addprefix graph/,$(G))
	python3 src/create_deg_chart.py $(addprefix degree/,$(G))