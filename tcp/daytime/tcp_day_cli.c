#include "tcp_wrap.h" 

int main(int argc, char **argv)
{
  int                sockfd, n;
  char               recvline[MAXLINE+1];
  struct sockaddr_in servaddr;

  if (argc != 2)
    err_quit("usage: tcp_day_cli <IPaddress>");

  sockfd = Socket(AF_INET, SOCK_STREAM, 0); 
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(13);
  Inet_aton(argv[1], &servaddr.sin_addr);

  Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
  
  while ((n = Read(sockfd, recvline, MAXLINE)) > 0) 
  {
    recvline[n] = 0;
    Fputs(recvline, stdout);
  }

  exit(0);
}				
