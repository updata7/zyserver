#include "NetWork.h"
#include "log.h"
#include "macro.h"
#include "malloc.h"

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <iostream>

NetWork::NetWork(struct server_config_t *sc)
{
	server_config = sc;
}

NetWork::~NetWork()
{
}

void NetWork::OnClientClose(socket_t fd, void *userdata)
{
	std::cout << "OnClientClose fd = " << fd << std::endl;
}

void NetWork::RegServerConnectedCb(net_work_callback cb, void *userdata)
{
	net_work_reg_onserverconnected(cb, userdata);
}

void NetWork::RegServerClosedCb(net_work_callback cb, void *userdata)
{
	net_work_reg_onserverclosed(cb, userdata);
}

void NetWork::RegClientIn(net_work_callback cb, void *userdata)
{
	net_work_reg_onclientin(cb, userdata);
}

void NetWork::RegClientOut(net_work_callback cb, void *userdata)
{
	net_work_reg_onclientout(cb, userdata);
}

void NetWork::SendMsg(SERVANT_TYPE servant, const char *msg)
{
	// 总长度(4字节)+servant长度(10字节)+msg长度
	int msg_len = strlen(msg);
	int final_msg_len = 4+msg_len+SERVANT_SIZE;
	char *final_msg = NEW char[final_msg_len];
	memset(final_msg, 0, final_msg_len);
	char sp[SERVANT_SIZE+1] = {0}; 	// 不+1 会导致 sprintf 溢出
	sprintf(final_msg, "%04d", msg_len+SERVANT_SIZE);
	sprintf(sp, "0x%08X", (unsigned int)servant);
	strncat(final_msg, sp, SERVANT_SIZE);
	strcat(final_msg, msg);

	log_debug("NetWork:SendMsg final_msg(%s) final_msg_len(%d)", final_msg, final_msg_len);
	send_msg(servant, final_msg, final_msg_len);
	DELETE final_msg;
}

void NetWork::Start()
{
	net_work_init();
	// net_work_reg_onclientclose(OnClientClose, this);

	net_work_run(server_config->address, server_config->port, 
		server_config->endpointlist, server_config->prefix);
}