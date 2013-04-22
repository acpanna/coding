subgradient_verfahren:	main.o subgradient_verfahren.o 
		g++ -Wall -o subgradient_verfahren main.o subgradient_verfahren.o
main.o:		main.cpp
		g++ -Wall -c main.cpp
subgradient_verfahren.o:	subgradient_verfahren.cpp subgradient_verfahren.h defs.h
		g++ -Wall -c subgradient_verfahren.cpp
clean:
		rm *.o
