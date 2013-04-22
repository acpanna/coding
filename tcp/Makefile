CC = gcc
CFLAGS = 
CPPFLAGS =

LIBS = -lnsl -lsocket -lresolv
OBJECTS = tcp-es10.o wrapper.o auxiliary.o error.o

all:		tcp-es10

tcp-es10:	$(OBJECTS)
		$(CC) -o tcp-es10 $(OBJECTS) $(LIBS)

$(OBJECTS):	unp.h

clean:
		-rm *.o

veryclean:	clean
		-rm tcp-es10


COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
