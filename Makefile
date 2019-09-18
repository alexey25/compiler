all:
	g++ -Wall src/*.cpp -o main
.PHONY: g 
g:
	dot -Tps graph.gv -o graph.ps

