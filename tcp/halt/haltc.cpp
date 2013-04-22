#include <winsock2.h>
#include <iostream.h>

int main(void)
{
	struct sockaddr_in peer;
    
	SOCKET sockfd;
  	
	peer.sin_family = AF_INET;
	peer.sin_port = htons(7500);
	peer.sin_addr.s_addr = inet_addr("192.168.0.1");

	WSADATA wsadata;
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd == INVALID_SOCKET)
	{
		cout << "socket error ..." << endl;
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *) &peer, sizeof(peer)) != 0)
	{
		cout << "connect error ..." << endl;
		exit(1);
	}

 	if(send(sockfd, "rundll32 user.exe,ExitWindows", 29, 0) <= 0)
	{
		cout << "send error ..." << endl;
		exit(1);
	}

	return 0;
}