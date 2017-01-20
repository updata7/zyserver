#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>  
#include <string.h>

#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

void _fprintf(const char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
}

int main()
{
	int listenfd;
	int port = 8889;
	struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  

    if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)  
        _fprintf("socket");
    
    fprintf(stdout, "server start. listening for %d\n", port);
    int on = 1;  
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        _fprintf("setsockopt");  
  
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        _fprintf("bind");

    if (listen(listenfd, SOMAXCONN) < 0)
        _fprintf("listen");

    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int conn = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
    char sendbuf[] = "welcome.";
    write(conn, "welcome", sizeof(sendbuf));
    fprintf(stdout, "ip=%s port=%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

	return 0;
}