#include <iostream>
#include <signal.h>
#include <string.h>

#include "log.h"
#include "timer.h"
#include "server_env.h"
#include "server_config.h"
#include "CommonClass.h"
#include "ServerStart.h"
#include "malloc.h"
#include "zredis.h"

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
	int redisable = atoi(get_env_value("redisable", "0"));
	init_server_config(address, port, prefix, logpath, endpointlist, thread, dbenable);

	if (redisable) {
		const char *redishost = get_env_value("redishost", "127.0.0.1");
		const int redisport = atoi(get_env_value("redisport", "6379"));
		struct timeval timeout = {2, 0}; 	// 超时时间2s
		redis_connect(redishost, redisport, timeout);
	}

	if (dbenable) {
		int dbport = atoi(get_env_value("dbport", "3306"));
		const char *dbhost = get_env_value("dbhost", "127.0.0.1");
		const char *dbname = get_env_value("dbname", "test_db");
		const char *dbuser = get_env_value("dbuser", "root");
		const char *dbpwd = get_env_value("dbpwd", "123456");
		init_db_config(dbhost, dbport, dbname, dbuser, dbpwd);
		ServerStart *server = NEW ServerStart(get_server_config(), get_db_config());
		server->Start();
		DELETE server;
	} else {
		ServerStart *server = NEW ServerStart(get_server_config());
		server->Start();
		DELETE server;
	}

	if (redisable) {
		redis_free();
	}
	
	log_release();
	return 0;
}