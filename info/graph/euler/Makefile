all:		euler

euler:		main.o graph.o
		g++ -Wall -o euler main.o graph.o
main.o:		main.cpp
		g++ -Wall -c main.cpp
graph.o:	graph.cpp	
		g++ -Wall -c graph.cpp
clean:
		rm *.o
