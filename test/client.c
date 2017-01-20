#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>  
#include <string.h>

#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)  

int main()
{
	int port = 8888;
	int sock;  
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  
        ERR_EXIT("socket");

	struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)  
        ERR_EXIT("connect");  
  
    struct sockaddr_in localaddr;  
    socklen_t addrlen = sizeof(localaddr);  
    if (getsockname(sock, (struct sockaddr*)&localaddr, &addrlen) < 0)  
        ERR_EXIT("getsockname");  
  
    printf("ip=%s port=%d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port)); 

    char sendbuf[1024] = {0};

    char recvbuf[1024] = {0};
    read(sock, recvbuf, sizeof(recvbuf));
    fputs(recvbuf, stdout);
    
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL) {
        write(sock, sendbuf, strlen(sendbuf));  
        memset(sendbuf, 0, sizeof(sendbuf));
    }

	return 0;
}