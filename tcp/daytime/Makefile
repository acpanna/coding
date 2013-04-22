all:		tcp_day_serv tcp_day_cli
tcp_day_serv:	tcp_day_serv.o tcp_wrap.o 
		gcc -Wall -o tcp_day_serv tcp_day_serv.o tcp_wrap.o
tcp_day_serv.o: tcp_day_serv.c 
		gcc -Wall -c tcp_day_serv.c
tcp_day_cli:	tcp_day_cli.o tcp_wrap.o 
		gcc -Wall -o tcp_day_cli tcp_day_cli.o tcp_wrap.o
tcp_day_cli.o:  tcp_day_cli.c  
		gcc -Wall -c tcp_day_cli.c
tcp_wrap.o:	tcp_wrap.c
		gcc -Wall -c tcp_wrap.c
clean:		
		rm *.o
