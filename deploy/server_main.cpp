#include <iostream>
#include <signal.h>
#include <string.h>

#include "log.h"
#include "timer.h"
#include "server_env.h"
#include "server_config.h"
#include "CommonClass.h"
#include "MasterDbInfo.h"
#include "ServerStart.hpp"
#include "Memory.hpp"

using namespace std;

int main(int argc, char *argv[])
{
#ifndef _WIN32
	// linux下需要屏蔽的一些信号
    signal( SIGHUP, SIG_IGN );
    signal( SIGALRM, SIG_IGN );
    signal( SIGPIPE, SIG_IGN );
    signal( SIGXCPU, SIG_IGN );
    signal( SIGXFSZ, SIG_IGN );
    signal( SIGPROF, SIG_IGN ); 
    signal( SIGVTALRM, SIG_IGN );
    signal( SIGQUIT, SIG_IGN );
    signal( SIGCHLD, SIG_IGN );
#else
    // nothing to do
#endif

	const char *machine_conf = NULL;
	const char *config = NULL;
	const char *logpath = NULL;
	int c;
	while (-1 != (c = getopt(argc, argv, 
		"m:"
		"c:"
		"l:"))){
		switch(c) {
			case 'm':
				machine_conf = optarg;
				break;
			case 'c':
				config = optarg;
				break;
			case 'l':
				logpath = optarg;
				break;
			default:
				cout<<"invalid param "<< c <<endl;
				break;
		}
	}
	
	log_init(logpath);
	timer_init();
	env_init(machine_conf, config);
	
	const char *address = get_env_value("address", "127.0.0.1");
	int port = atoi(get_env_value("port", "8000"));
	int prefix = strtol(get_env_value("prefix", "0x0001"), NULL, 16);
	const char *endpointlist = get_env_value("endpointlist", NULL);
	int thread = atoi(get_env_value("thread", "2"));
	int dbenable = atoi(get_env_value("dbenable", "0"));
	init_server_config(address, port, prefix, logpath, endpointlist, thread, dbenable);

	ServerStart *server = NEW ServerStart(get_server_config());
	server->Start();

	DELETE server;
	log_release();
	return 0;
}