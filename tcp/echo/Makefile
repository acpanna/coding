all:			tcp_echo_serv tcp_echo_serv2 tcp_echo_serv3 tcp_echo_cli2 tcp_echo_cli
tcp_echo_serv:		tcp_echo_serv.o tcp_wrap.o 
			gcc -Wall -o tcp_echo_serv tcp_echo_serv.o tcp_wrap.o
tcp_echo_serv.o:	tcp_echo_serv.c 
			gcc -Wall -c tcp_echo_serv.c
tcp_echo_serv2:		tcp_echo_serv2.o tcp_wrap.o
			gcc -Wall -o tcp_echo_serv2 tcp_echo_serv2.o tcp_wrap.o
tcp_echo_serv2.o:	tcp_echo_serv2.c
			gcc -Wall -c tcp_echo_serv2.c
tcp_echo_serv3:		tcp_echo_serv3.o tcp_wrap.o
			gcc -Wall -o tcp_echo_serv3 tcp_echo_serv3.o tcp_wrap.o
tcp_echo_serv3.o:	tcp_echo_serv3.c
			gcc -Wall -c tcp_echo_serv3.c 
tcp_echo_cli2:		tcp_echo_cli2.o tcp_wrap.o
		        gcc -Wall -o tcp_echo_cli2 tcp_echo_cli2.o tcp_wrap.o
tcp_echo_cli2.o:	tcp_echo_cli2.c
		        gcc -Wall -c tcp_echo_cli2.c 
tcp_echo_cli:		tcp_echo_cli.o tcp_wrap.o 
			gcc -Wall -o tcp_echo_cli tcp_echo_cli.o tcp_wrap.o
tcp_echo_cli.o:  	tcp_echo_cli.c  
			gcc -Wall -c tcp_echo_cli.c
tcp_wrap.o:		tcp_wrap.c
			gcc -Wall -c tcp_wrap.c
clean:		
			rm *.o
