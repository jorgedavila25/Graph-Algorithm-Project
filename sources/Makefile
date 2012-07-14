#Graph
# files: source files:  main.cpp dijkstra.cpp
#        header file:  dijkstra.h LeftistHeap.h Vertex.h
# executable file: Graph
#
# first define target file : Graph 
#              dependencies are the object files that build the program

make all: main.o dijkstra.o
	g++ -o prog5 main.cpp dijkstra.cpp

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

main.o: main.cpp
	g++ -c main.cpp

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

#Clean obj files

clean:
	(rm -f *.o;)
# that's all
