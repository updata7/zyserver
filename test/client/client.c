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

#include "flatcc_builder.h"
#include "flatcc/support/elapsed.h"
#include "login_builder.h"

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

int port = 8000;
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
    fd_set rset;  
    FD_ZERO(&rset);  
  
    int nready;  
    int maxfd;  
    int fd_stdin = fileno(stdin);  
    if (fd_stdin > sock)  
        maxfd = fd_stdin;  
    else  
        maxfd = sock;  
    
    int i;
    char sendbuf[1024+4] = {0};
    char sendbuf2[1024] = {0};

    messagelen = messagelen > 1024 ? 1024 : messagelen;
    messagelen = messagelen < 15 ? 15 : messagelen;
    sprintf(sendbuf, "%04d", messagelen);
    strcat(sendbuf, "0x00010001");
    for (i = 14; i < messagelen+4; i ++) {
        sendbuf[i] = '6';
    }

    char recvbuf[1024] = {0};  
    char sendbuf1[1024] = {0};
    int stdineof = 0;  
    i = 0;
    maxfd += 1;
    // if (fgets(sendbuf2, sizeof(sendbuf2), stdin) != NULL) {
    //     write(sock, sendbuf, strlen(sendbuf));  
    //     memset(sendbuf, 0, sizeof(sendbuf));
    // }

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
  
        // if (FD_ISSET(sock, &rset))  
        // {  
        //     int ret = readline(sock, recvbuf, sizeof(recvbuf));  
        //     if (ret == -1)  
        //         ERR_EXIT("readline");  
        //     else if (ret == 0)  
        //     {  
        //         printf("server close\n");  
        //         break;  
        //     }  

        //     fputs(recvbuf, stdout);  
        //     memset(recvbuf, 0, sizeof(recvbuf));  
        // }  
        if (FD_ISSET(fd_stdin, &rset))  
        {  
            // if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)  
            // {  
            //     stdineof = 1;  
                 
            //     close(sock); 
            //     sleep(5); 
            //     exit(EXIT_FAILURE); 
                  
            //     shutdown(sock, SHUT_WR);  
            // }  
            // else
            // { 
                
                    // flatcc_builder_t builder, *B;
                    // size_t size;
                    // B = &builder;
                    // char *buffer;
                    // flatcc_builder_init(B);

                    // flatbuffers_string_ref_t nick_name = flatbuffers_string_create_str(B, "n1");
                    // flatbuffers_string_ref_t password = flatbuffers_string_create_str(B, "p1");

                    // flatbuffers_string_ref_t player_id = flatbuffers_string_create_str(B, "");
                    // flatbuffers_string_ref_t session = flatbuffers_string_create_str(B, "");

                    // request_ref_t rt = request_create(B, nick_name, password);
                    // response_ref_t st = response_create(B, 0, player_id, session);
                    // Protocol_create_as_root(B, rt, st);
                    // buffer = flatcc_builder_finalize_buffer(B, &size);

                    // =====================================
                    // Protocol_table_t pt = Protocol_as_root(buffer);


                    // request_table_t rt2 = Protocol_request(pt);

                    // const char *nick_name2 = request_nick_name(rt2);
                    // const char *password2 = request_password(rt2);

                    // fprintf(stderr, "add receive:nick_name(%s) password(%s)\n", nick_name2, password2);
                    // ======================================
                    
                    // assert(buffer);
                    // writen(sock, buffer, size);
                    // free(buffer);
                

            //     write(sock, sendbuf, strlen(sendbuf));  
            //     memset(sendbuf, 0, sizeof(sendbuf));
            // }
        }
        write(sock, sendbuf, strlen(sendbuf));  
        memset(sendbuf, 0, sizeof(sendbuf));
    }  

    // while(1) {
    //     pthread_mutex_lock(&mutex);
    //     write(sock, sendbuf, strlen(sendbuf));  
    //     // memset(sendbuf, 0, sizeof(sendbuf));
    //     pthread_mutex_unlock(&mutex);
    //     ++ i;
    //     if (i >= send_count) {
    //         break;
    //     }
    // }

    // close(sock);
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
    const char *ip = NULL;

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