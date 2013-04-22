gradient_verfahren:	main.o gradient_verfahren.o armijo.o
		g++ -Wall -o gradient_verfahren main.o gradient_verfahren.o armijo.o
main.o:		main.cpp
		g++ -Wall -c main.cpp
gradient_verfahren.o:	gradient_verfahren.cpp gradient_verfahren.h defs.h
		g++ -Wall -c gradient_verfahren.cpp
armijo.o: 	armijo.cpp armijo.h defs.h
		g++ -Wall -c armijo.cpp
clean:
		rm *.o
