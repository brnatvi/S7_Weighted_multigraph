
all: multigraph

multigraph: Sommet.cpp Arete.cpp  Graph.cpp test.cpp
	g++ --std=c++11 -Wall -o multigraph Sommet.cpp Arete.cpp  Graph.cpp test.cpp


clean:
	rm -rf multigraph *.o