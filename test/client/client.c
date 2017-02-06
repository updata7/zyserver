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
#include <fcntl.h>  
#include <sys/wait.h>  
#include <sys/epoll.h>

#include "flatcc_builder.h"
#include "flatcc/support/elapsed.h"
#include "login_builder.h"

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

int port = 8002;
int pthread_num = 2;
int messagelen = 20;
pthread_mutex_t mutex;

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
    int i;
    char sendbuf[1024+4] = {0};
    char sendbuf2[1024] = {0};
    char recvbuf[1024] = {0};  
    messagelen = messagelen > 1024 ? 1024 : messagelen;
    messagelen = messagelen < 15 ? 15 : messagelen;
    sprintf(sendbuf, "%04d", messagelen);
    strcat(sendbuf, "0x00010001");
    for (i = 14; i < messagelen+4; i ++) {
        sendbuf[i] = '6';
    }

    int epollfd;  
    epollfd = epoll_create1(EPOLL_CLOEXEC); 
    int fd_stdin = fileno(stdin);
    struct epoll_event event;  
    event.data.fd = fd_stdin;  
    event.events = EPOLLIN | EPOLLET;  
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd_stdin, &event);
    
    event.data.fd = sock;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &event);

    struct epoll_event events[2];
    while (1)
    {
        int n = epoll_wait(epollfd, events, 2, 0);

        if (n == -1)  
        {  
            if (errno == EINTR)
                continue;  
              
            exit(1);
        }  
        if (n == 0)  
            continue;

        for (i = 0; i < n; i ++) {
            if (events[i].events & EPOLLIN) {
                if (events[i].data.fd == fd_stdin) {
                    if (fgets(sendbuf2, sizeof(sendbuf2), stdin) == NULL)  
                    {
                        event = events[i];  
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, fd_stdin, &event);
                    } else {
                        write(sock, sendbuf, strlen(sendbuf));  
                        // memset(sendbuf, 0, sizeof(sendbuf));
                        memset(sendbuf2, 0, sizeof(sendbuf2));
                    }
                } else if(events[i].data.fd == sock) {
                    int recv_size = readline(sock, recvbuf, 1024);
                    printf("%s\n", recvbuf);
                }
            }
        }
    }  

    close(epollfd);
    close(sock);
}
  
void handle_sigpipe(int sig)  
{  
    printf("recv a sig=%d\n", sig);  
} 

void *pthread_cl(void *argv)
{
    struct sockaddr_in *servaddr = (struct sockaddr_in *)argv;

    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  
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
  
int main(int argc, char *argv[])  
{
    const char *ip = "127.0.0.1";

    int c;
    while (-1 != (c = getopt(argc, argv, 
        "a:"
        "t:"
        "l:"
        "p:"))){
        switch(c) {
            case 'a':
                ip = optarg;
                break;
            case 't':
                pthread_num = atoi(optarg);
                break;
            case 'l':
                messagelen = atoi(optarg);
                break;
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "invalid param %c\n", c);
                break;
        }
    }

    if (pthread_mutex_init(&mutex, NULL)) {
        fprintf(stderr, "Init mutex error");
        exit(1);
    }

    signal(SIGPIPE, SIG_IGN);
    struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);  
    // servaddr.sin_addr.s_addr = inet_addr("10.21.210.242"); 
    servaddr.sin_addr.s_addr = inet_addr(ip); 
    
    int i = 0;
    pthread_t pd[pthread_num];
    for (i = 0; i < pthread_num; i ++)
    {
        pthread_create(&pd[i], NULL, pthread_cl, (void *)&servaddr);
    }

    for (i = 0; i < pthread_num; i ++)
    {
        pthread_join(pd[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;  
}