isdncheckd:		isdncheckd.o tcp_wrap.o 
			gcc -Wall -o isdncheckd isdncheckd.o tcp_wrap.o
isdncheckd.o:		isdncheckd.c 
			gcc -Wall -c isdncheckd.c
tcp_wrap.o:		tcp_wrap.c
			gcc -Wall -c tcp_wrap.c
clean:		
			rm *.o
