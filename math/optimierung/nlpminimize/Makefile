nlpminimize:	main.o nlpminimize.o simplex.o armijo.o
		g++ -Wall -o nlpminimize main.o nlpminimize.o simplex.o armijo.o
main.o:		main.cpp
		g++ -Wall -c main.cpp
nlpminimize.o:	nlpminimize.cpp nlpminimize.h defs.h
		g++ -Wall -c nlpminimize.cpp
simplex.o:	simplex.cpp simplex.h defs.h
		g++ -Wall -c simplex.cpp
armijo.o: 	armijo.cpp armijo.h defs.h
		g++ -Wall -c armijo.cpp
clean:
		rm *.o
