#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <signal.h>
#include <pthread.h>
  
#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>  
#include <string.h>  
  
#define ERR_EXIT(m) \  
        do \  
        { \  
                perror(m); \  
                exit(EXIT_FAILURE); \  
        } while(0)  

static const int PORT = 9995;
static const int pthread_num = 10;

ssize_t readn(int fd, void *buf, size_t count)  
{  
        size_t nleft = count;  
        ssize_t nread;  
        char *bufp = (char*)buf;  
  
        while (nleft > 0)  
        {  
                if ((nread = read(fd, bufp, nleft)) < 0)  
                {  
                        if (errno == EINTR)  
                                continue;  
                        return -1;  
                }  
                else if (nread == 0)  
                        return count - nleft;  
  
                bufp += nread;  
                nleft -= nread;  
        }  
  
        return count;  
}  
  
ssize_t writen(int fd, const void *buf, size_t count)  
{  
        size_t nleft = count;  
        ssize_t nwritten;  
        char *bufp = (char*)buf;  
  
        while (nleft > 0)  
        {  
                if ((nwritten = write(fd, bufp, nleft)) < 0)  
                {  
                        if (errno == EINTR)  
                                continue;  
                        return -1;  
                }  
                else if (nwritten == 0)  
                        continue;  
  
                bufp += nwritten;  
                nleft -= nwritten;  
        }  
  
        return count;  
}  
  
ssize_t recv_peek(int sockfd, void *buf, size_t len)  
{  
        while (1)  
        {  
                int ret = recv(sockfd, buf, len, MSG_PEEK);  
                if (ret == -1 && errno == EINTR)  
                        continue;  
                return ret;  
        }  
}  
  
  
ssize_t readline(int sockfd, void *buf, size_t maxline)  
{  
        int ret;  
        int nread;  
        char *bufp = buf;  
        int nleft = maxline;  
        while (1)  
        {  
                ret = recv_peek(sockfd, bufp, nleft);  
                if (ret < 0)  
                        return ret;  
                else if (ret == 0)  
                        return ret;  
  
                nread = ret;  
                int i;  
                for (i=0; i<nread; i++)  
                {  
                        if (bufp[i] == '\n')  
                        {  
                                ret = readn(sockfd, bufp, i+1);  
                                if (ret != i+1)  
                                        exit(EXIT_FAILURE);  
  
                                return ret;  
                        }  
                }  
  
                if (nread > nleft)  
                        exit(EXIT_FAILURE);  
  
                nleft -= nread;  
                ret = readn(sockfd, bufp, nread);  
                if (ret != nread)  
                        exit(EXIT_FAILURE);  
  
                bufp += nread;  
        }  
  
        return -1;  
}  
  
void echo_cli(int sock)  
{  
    /* 
        char sendbuf[1024] = {0}; 
            char recvbuf[1024] = {0}; 
            while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) 
            { 
                    writen(sock, sendbuf, strlen(sendbuf)); 
     
                    int ret = readline(sock, recvbuf, sizeof(recvbuf)); 
                    if (ret == -1) 
                            ERR_EXIT("readline"); 
                    else if (ret == 0) 
                    { 
                            printf("client close\n"); 
                            break; 
                    } 
     
                    fputs(recvbuf, stdout); 
                    memset(sendbuf, 0, sizeof(sendbuf)); 
                    memset(recvbuf, 0, sizeof(recvbuf)); 
            } 
     
            close(sock); 
    */  
  
    fd_set rset;  
    FD_ZERO(&rset);  
  
    int nready;  
    int maxfd;  
    int fd_stdin = fileno(stdin);  
    if (fd_stdin > sock)  
        maxfd = fd_stdin;  
    else  
        maxfd = sock;  
  
    char sendbuf[1024] = "hello world."  
    char recvbuf[1024] = {0};  
  
    int stdineof = 0;  
  
    while (1)  
    {  
        if (stdineof == 0)  
            FD_SET(fd_stdin, &rset);  
        FD_SET(sock, &rset);  
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);  
        if (nready == -1)  
            ERR_EXIT("select");  
  
        if (nready == 0)  
            continue;  
  
        if (FD_ISSET(sock, &rset))  
        {  
            int ret = readline(sock, recvbuf, sizeof(recvbuf));  
            if (ret == -1)  
                    ERR_EXIT("readline");  
            else if (ret == 0)  
            {  
                    printf("server close\n");  
                    break;  
            }  

            fputs(recvbuf, stdout);  
            memset(recvbuf, 0, sizeof(recvbuf));  
        }  
        if (FD_ISSET(fd_stdin, &rset))  
        {  
            if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)  
            {  
                stdineof = 1;  
                /* 
                close(sock); 
                sleep(5); 
                exit(EXIT_FAILURE); 
                */  
                shutdown(sock, SHUT_WR);  
            }  
            else  
            {  
                writen(sock, sendbuf, strlen(sendbuf));  
                memset(sendbuf, 0, sizeof(sendbuf));  
            }
        }  
    }  
}  
  
void handle_sigpipe(int sig)  
{  
    printf("recv a sig=%d\n", sig);  
} 

void *pthread_cl(void *argv)
{
    struct sockaddr_in *servaddr = (struct sockaddr_in *)argv;

    int sock;  
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  
        ERR_EXIT("socket");  
  

    if (connect(sock, (struct sockaddr*)servaddr, sizeof(*servaddr)) < 0)  
        ERR_EXIT("connect");  
  
    struct sockaddr_in localaddr;  
    socklen_t addrlen = sizeof(localaddr);  
    if (getsockname(sock, (struct sockaddr*)&localaddr, &addrlen) < 0)  
        ERR_EXIT("getsockname");  
  
    printf("ip=%s port=%d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));  
  
  
    echo_cli(sock); 
    return NULL;
}
  
int main(void)  
{  
/* 
    signal(SIGPIPE, handle_sigpipe); 
*/      
    signal(SIGPIPE, SIG_IGN);
    struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(PORT);  
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
    // void *res = NULL;
    // int s;
    int i = 0;
    pthread_t pd[pthread_num];
    for (i = 0; i < pthread_num; i ++)
    {
        pthread_create(&pd[i], NULL, pthread_cl, (void *)&servaddr);
    }

    // for (i = 0; i < pthread_num; i ++)
    // {
    //     s = pthread_join(pd[i], &res);
    //     if (s != 0)
    //     {
    //         ERR_EXIT(s);
    //     }
    //     free(res);
    // }

    pthread_exit(0);

    return 0;  
}