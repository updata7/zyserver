#include <event2/event.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include <sys/socket.h>
#include <netinet/tcp.h>

#include <string.h>
#include <stdlib.h>

int64_t total_bytes_read = 0;
int64_t total_messages_read = 0;

static void set_tcp_no_delay(evutil_socket_t fd)
{
  int one = 1;
  setsockopt(fd, IPPROTO_TCP, TCP_NODELAY,
      &one, sizeof one);
}

static void readcb(struct bufferevent *bev, void *ctx)
{
  char msg[1024];
  size_t n;
  for (;;) {
    n = bufferevent_read(bev, msg, 1024);
    if (n <= 0) {
      break;
    }
    fprintf(stderr, "%s", msg);
  }
}

static void writecb(struct bufferevent *bev, void *ctx)
{
  char sendbuf[1024] = "hi\n";

  printf("=============\n");
  while (fgets(sendbuf, sizeof(sendbuf), stdin)) {
    fprintf(stderr, "send msg: %s || success.\n", sendbuf);
    bufferevent_write(bev, sendbuf, strlen(sendbuf));
  }
}

static void eventcb(struct bufferevent *bev, short events, void *ptr)
{
  if (events & BEV_EVENT_CONNECTED) {
    evutil_socket_t fd = bufferevent_getfd(bev);
    set_tcp_no_delay(fd);
  } else if (events & BEV_EVENT_ERROR) {
    printf("NOT Connected\n");
  }
}

int main(int argc, char **argv)
{
  struct event_base *base;
  struct sockaddr_in sin;
  int port = 8888;

  base = event_base_new();
  if (!base) {
    printf("Couldn't open event base\n");
    return 1;
  }

  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = htonl(0x7f000001); /* 127.0.0.1 */
  sin.sin_port = htons(port);

  struct bufferevent *bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

  bufferevent_setcb(bev, readcb, writecb, eventcb, NULL);
  bufferevent_enable(bev, EV_READ|EV_WRITE);
  if (bufferevent_socket_connect(bev,
        (struct sockaddr *)&sin, sizeof(sin)) < 0) {
    /* Error starting connection */
    bufferevent_free(bev);
    puts("error connect");
    return -1;
  }

  event_base_dispatch(base);
  bufferevent_free(bev);
  event_base_free(base);

  return 0;
}