#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define SA             struct sockaddr
#define MAXLINE        256
#define SERV_PORT      9123
#define POLLRDNORM     0x0040

typedef void Sigfunc(int);

/*---------------------------------------------------------------------------*/
/*                  Wrapperfunktionen der Socketfunktionen                   */
/*---------------------------------------------------------------------------*/  

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
void Connect(int fd, const struct sockaddr *sa, socklen_t salen);
void Bind(int fd, const struct sockaddr *sa, socklen_t salen);
void Listen(int fd, int backlog);
int Socket(int family, int type, int protocol);

/*---------------------------------------------------------------------------*/
/*                   Wrapperfunktionen der Hilfsfunktionen                   */
/*---------------------------------------------------------------------------*/ 

void Inet_pton(int family, const char *strptr, void *addrptr);
void Inet_aton(const char *strptr, struct in_addr *addrptr);
char * Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);

/*---------------------------------------------------------------------------*/
/*            Wrapperfunktionen der Standard-Ein-/Ausgabefunktionen          */
/*---------------------------------------------------------------------------*/  

void Close(int fd);
void Shutdown(int s, int how);
ssize_t Read(int fd, void *ptr, size_t nbytes);
char * Fgets(char *ptr, int n, FILE *stream);
void Fputs(const char *ptr, FILE *stream);
void Write(int fd, void *ptr, size_t nbytes);
ssize_t readline(int fd, void *vptr, size_t maxlen); 
ssize_t Readline(int fd, void *ptr, size_t maxlen);
ssize_t writen(int fd, const void *vptr, size_t n);
void Writen(int fd, void *ptr, size_t nbytes);

/*---------------------------------------------------------------------------*/
/*                     Wrapperfunktionen der Exit-Funktion                   */
/*---------------------------------------------------------------------------*/

void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);

/*---------------------------------------------------------------------------*/
/*              Wrapperfunktionen der Standard-Systemfunktionen              */
/*---------------------------------------------------------------------------*/

pid_t Fork(void);

/*---------------------------------------------------------------------------*/
/*                    Wrapperfunktionen fuer Signal-Handler                  */
/*---------------------------------------------------------------------------*/
   
void sig_chld(int signo);
Sigfunc * Signal (int signo, Sigfunc *func);

/*---------------------------------------------------------------------------*/
/*                    Wrapperfunktionen fuer I/O-Multiplexing                */
/*---------------------------------------------------------------------------*/
     
int Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int Poll(struct pollfd *ufds, unsigned int nfds, int timeout);
