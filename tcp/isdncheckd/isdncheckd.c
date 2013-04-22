#include "tcp_wrap.h" 
  
#define LISTENQ   32

void str_serv(int sockfd); 

int main(int argc, char **argv) 
{ 
  int                listenfd, connfd; 
  pid_t              childpid; 
  socklen_t          clilen; 
  struct sockaddr_in cliaddr, servaddr; 
  
  listenfd = Socket(AF_INET, SOCK_STREAM, 0); 
  bzero(&servaddr, sizeof(servaddr)); 
  servaddr.sin_family      = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  servaddr.sin_port        = htons(SERV_PORT); 
  
  Bind(listenfd, (SA *) &servaddr, sizeof(servaddr)); 
  Listen(listenfd, LISTENQ); 
  Signal(SIGCHLD, sig_chld);
  
  for (;;)
  {
    clilen = sizeof(cliaddr); 
    
    if((connfd = Accept(listenfd, (SA *) &cliaddr, &clilen)) < 0)
    { 
      if (errno == EINTR) 
        continue; 
      else 
        err_sys("accept error");
    }
    
    if ((childpid = Fork()) == 0) 
    {
      Close(listenfd); 
      str_serv(connfd); 
      exit(0); 
    } 
    
    Close(connfd); 
  } 
} 

void str_serv(int sockfd)
{
  char $line:
  ssize_t n;

  system("export ISDNCHECK=$(isdncheck.pl 22)");
  line = getenv(ISDNCHECK);
  n = strlen(line);
 
  Writen(sockfd, line, n);
}       
