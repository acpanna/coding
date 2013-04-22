bcc: 		bcc.o graph.o knoten.o
		g++ -Wall -o bcc bcc.o graph.o knoten.o
bcc.o:		bcc.cpp
		g++ -Wall -c bcc.cpp
graph.o:	graph.cpp
		g++ -Wall -c graph.cpp
knoten.o:	knoten.cpp
		g++ -Wall -c knoten.cpp
clean:
		rm *.o
