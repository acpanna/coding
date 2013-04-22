#include "tcp_wrap.h" 

#define max(x, y) ((x) > (y) ? (x) : (y)) 

void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv)
{ 
  int                sockfd; 
  struct sockaddr_in servaddr; 
  
  if (argc != 2) 
    err_quit("usage: %s <IPaddress>", argv[0]); 
  
  sockfd = Socket(AF_INET, SOCK_STREAM, 0); 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port   = htons(SERV_PORT); 
  Inet_pton(AF_INET, argv[1], &servaddr.sin_addr); 
  
  Connect(sockfd, (SA *) &servaddr, sizeof(servaddr)); 
  str_cli(stdin, sockfd); 
  
  return 0;
}

void str_cli(FILE *fp, int sockfd)
{
  int    ndfs, stdineof;
  fd_set rset;
  char   sendline[MAXLINE], recvline[MAXLINE];
       
  stdineof = 0;
  FD_ZERO(&rset);
	 
  for (;;)
  {
    if (stdineof == 0)
      FD_SET(fileno(fp), &rset);
    
    FD_SET(sockfd, &rset);
    ndfs = max(fileno(fp), sockfd) + 1;
    Select(ndfs, &rset, NULL, NULL, NULL);
	     
    if (FD_ISSET(sockfd, &rset))
    {
      if (Readline(sockfd, recvline, MAXLINE) == 0)
      {
	if (stdineof == 1)
	  return;
	else
	  err_quit("str_cli : server terminated prematurely");
      }
      
      Fputs(recvline, stdout);
    }
				 
    if (FD_ISSET(fileno(fp), &rset))
    {
      if (Fgets(sendline, MAXLINE, fp ) == NULL)
      {
        stdineof = 1;
	Shutdown(sockfd, SHUT_WR);
	FD_CLR(fileno(fp), &rset);
	continue;
      }
							       
      Writen(sockfd, sendline, strlen(sendline));
    }
  }   
} 
