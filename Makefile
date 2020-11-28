CC = gcc
G = simple_graph.txt
W = 2147483647

make:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(G)) $(W)
	g++ src/random.cpp -o random --std=c++17
	./random $(addprefix graph/,$(G)) $(W)
	g++ src/asce.cpp -o asce --std=c++17
	./asce $(addprefix graph/,$(G)) $(W)
	g++ src/desce.cpp -o desce --std=c++17
	./desce $(addprefix graph/,$(G)) $(W)
	g++ src/count_degree.cpp -o count_degree --std=c++17
	./count_degree $(addprefix graph/,$(G))
	g++ src/walk.cpp -o walk --std=c++17
	./walk $(addprefix graph/,$(G)) $(W)
	python3 src/create_integrated.py $(addprefix output/,$(G)) $(W)
	python3 src/create_deg-width.py $(addprefix output/,$(G)) $(W)

pq:
	g++ src/min-deg-heu.cpp -o min-deg-heu --std=c++17
	./min-deg-heu $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/,$(G))

random:
	g++ src/random.cpp -o random --std=c++17
	./random $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/random-,$(G))

asce:
	g++ src/asce.cpp -o desce --std=c++17
	./ace $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/asce-,$(G))

desce:
	g++ src/desce.cpp -o desce --std=c++17
	./desce $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/desce-,$(G))

walk:
	g++ src/walk.cpp -o walk --std=c++17
	./walk $(addprefix graph/,$(G)) $(W)
	python3 src/create_chart.py $(addprefix output/walk-,$(G))

deg:
	g++ src/count_degree.cpp -o count_degree --std=c++17
	./count_degree $(addprefix graph/,$(G))
	python3 src/create_deg_chart.py $(addprefix degree/,$(G))