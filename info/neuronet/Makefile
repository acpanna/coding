neuronet:	Test.o Neuron.o NeuroNet.o Pattern.o
		g++ -Wall -o neuronet Test.o Neuron.o NeuroNet.o Pattern.o
Test.o:		Test.cpp
		g++ -Wall -c Test.cpp
Neuron.o:	Neuron.cpp
		g++ -Wall -c Neuron.cpp
NeuroNet.o:	NeuroNet.cpp
		g++ -Wall -c NeuroNet.cpp
Pattern.o:	Pattern.cpp
		g++ -Wall -c Pattern.cpp
clean:
		rm *.o
