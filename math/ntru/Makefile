include ../../../rasa/Make.config

INC = ../../../rasa/src/
LIB = ..

all:	gen_ntru ntru2prb check_ntru

gen_ntru: gen_ntru.cpp 
	$(CC) $(CFLAGS) -o gen_ntru gen_ntru.cpp -I $(INC) -L $(LIB) -lrasa -lntl -lgmp 

ntru2prb: ntru2prb.cpp 
	$(CC) $(CFLAGS) -o ntru2prb ntru2prb.cpp -I $(INC) -L $(LIB) -lrasa -lntl -lgmp 

check_ntru:	check_ntru.cpp 
	$(CC) $(CFLAGS) -o check_ntru check_ntru.cpp -I $(INC) -L $(LIB) -lrasa 

clean:
	rm gen_ntru ntru2prb check_ntru *.o
