all:		threenf.cgi

threenf.cgi:	main.o fdmengen.o cgiparse.o cgimap.o cgipair.o cgipost.o
		g++ -Wall -o threenf.cgi main.o fdmengen.o cgiparse.o cgimap.o cgipair.o cgipost.o

main.o:		main.cpp
		g++ -Wall -c main.cpp
		
fdmengen.o:	fdmengen.cpp
		g++ -Wall -c fdmengen.cpp

cgiparse.o:     cgiparse.cpp
		g++ -Wall -c cgiparse.cpp

cgimap.o:	cgimap.cpp
		g++ -Wall -c cgimap.cpp

cgipair.o:	cgipair.cpp
		g++ -Wall -c cgipair.cpp

cgipost.o:	cgipost.cpp
		g++ -Wall -c cgipost.cpp

clean:		
		rm *.o
install:	
		cp threenf.html /usr/local/httpd/htdocs/threenf.html
		cp threenf.cgi /usr/local/httpd/cgi-bin/threenf.cgi
