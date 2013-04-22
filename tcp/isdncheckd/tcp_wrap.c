#include "tcp_wrap.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
  int n;

  if ((n = accept(fd, sa, salenptr)) < 0) 
    err_sys("accept error");
  
  return n;
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
  if (connect(fd, sa, salen) < 0)
    err_sys("connect error");
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
  if (bind(fd, sa, salen) < 0)
    err_sys("bind error");
}

void Listen(int fd, int backlog)
{
  if (listen(fd, backlog) < 0)
    err_sys("listen error");
}

int Socket(int family, int type, int protocol)
{
  int n;

  if ((n = socket(family, type, protocol)) < 0)
    err_sys("socket error");

  return n;
}

void Inet_pton(int family, const char *strptr, void *addrptr)
{
  int n;

  if ((n = inet_pton(family, strptr, addrptr)) < 0)
    err_sys("inet_pton error for %s: ", strptr); 
 
  else if (n == 0)
    err_quit("inet_pton error for %s", strptr);
}

void Inet_aton(const char *strptr, struct in_addr *addrptr)
{
  if (inet_aton(strptr, addrptr) <= 0)
    err_sys("inet_aton error");
}

char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
  char *ptr;

  if (strptr == NULL)
    err_quit("inet_ntop error: Empty string to convert");

  if ((ptr = (char *) inet_ntop(family, addrptr, strptr, len)) == NULL)
    err_quit("inet_ntop error: Error converting address");

  return ptr;
}

void Close(int fd)
{
  if (close(fd) == -1)
    err_sys("close error");
}

void Shutdown(int s, int how)
{
  if (shutdown(s, how) == -1)
    err_sys("shutdown error");	  
}

ssize_t	Read(int fd, void *ptr, size_t nbytes)
{
  ssize_t n;

  if ((n = read(fd, ptr, nbytes)) == -1)
    err_sys("read error");

  return n;
}

char * Fgets(char *ptr, int n, FILE *stream)
{
  char *rptr;
  
  if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
    err_sys("fgets error");

  return rptr;
}

void Fputs(const char *ptr, FILE *stream)
{
  if (fputs(ptr, stream) == EOF)
    err_sys("fputs error");
}

void Write(int fd, void *ptr, size_t nbytes)
{
  if (write(fd, ptr, nbytes) != nbytes)
    err_sys("write error");
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
  int n, rc;
  char c, *ptr;

  ptr = vptr;

  for (n=1; n<maxlen; n++) 
  {
    if ((rc = read(fd, &c , 1)) == 1) 
    {
      *ptr++ = c;

      if (c == '\n')
	break;       /* newline is stored, like fgets() */
    } 
    
    else if (rc == 0) 
    {
      if (n == 1)
        return 0;    /* EOF, keine Daten gelesen */

      else
        break;       /* EOF, Daten gelesen */
    } 
    
    else
      return -1;     /* Fehler, errno durch read gesetzt */
  }

  *ptr = 0;

  return n;
}            

ssize_t Readline(int fd, void *ptr, size_t maxlen)
{
  ssize_t n;

  if ((n = readline( fd, ptr, maxlen)) < 0)
    err_sys("readline error");

  return n;
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
  ssize_t nwritten;
	     
  if ((nwritten = write(fd, vptr, n)) <= 0)
    return -1;
	
  return n;
}   

void Writen(int fd, void *ptr, size_t nbytes)
{
  if (writen(fd, ptr, nbytes) != nbytes)
    err_sys("writen error");
}

void err_quit(const char *fmt, ...)
{
  va_list ap;
  char buf[MAXLINE];

  va_start(ap, fmt);

  vsnprintf(buf, sizeof(buf), fmt, ap);  
  strcat(buf, "\n");
  fflush(stderr);
  fputs(buf, stderr);

  va_end(ap);

  exit(1);
}

void err_sys(const char *fmt, ...)
{
  va_list ap;
  int errno_save, n;
  char buf[MAXLINE];

  va_start(ap, fmt);

  errno_save = errno; 
  vsnprintf(buf, sizeof(buf), fmt, ap);  
  n = strlen(buf);
  snprintf(buf+n, sizeof(buf)-n, ": %s (%d)", strerror(errno_save), errno_save);
  strcat(buf, "\n");
  fflush(stderr);
  fputs(buf, stderr);

  va_end(ap);
  exit(1);
}

pid_t Fork(void)
{
  pid_t pid;
	   
  if ((pid = fork()) == -1)
    err_sys("fork error");
	     
  return pid;
}

void sig_chld(int  signo) 
{ 
  pid_t pid; 
  int stat; 

  while((pid = waitpid(-1, &stat, WNOHANG)) > 0) 
    printf("child %d terminated \n", pid); 

  return; 
}

Sigfunc * Signal(int signo, Sigfunc *func) 
{ 
  struct sigaction act, oact; 
  act.sa_handler = func; 
  sigemptyset(&act.sa_mask); 
  act.sa_flags = 0; 

  if (signo == SIGALRM) 
  { 
    #ifdef SA_INTERRUPT 
      act.sa_flags |= SA_INTERRUPT;   /* SunOS 4.x */ 
    #endif 
  } 
  
  else 
  {
    #ifdef SA_RESTART 
      act.sa_flags |= SA_RESTART;     /* SVR4, 4.4BSD, Solaris */ 
    #endif 
  } 

  if (sigaction(signo, &act, &oact) < 0)
    return SIG_ERR; 
  
  return(oact.sa_handler); 
}

int Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout)
{
  int m = select(n, readfds, writefds, exceptfds, timeout);
  
  if (m == -1)
    err_sys("select error");

  return m;	    
}

int Poll(struct pollfd *ufds, unsigned int nfds, int timeout)
{
  int n = poll(ufds, nfds, timeout);

  if (n < 0)
    err_sys("poll error");

  return n;
}
