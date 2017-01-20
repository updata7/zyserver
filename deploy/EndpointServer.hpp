#ifndef ENDPOINTSERVER_H
#define ENDPOINTSERVER_H

class EndpointServer
{
public:
	EndpointServer(const char *Address, int Port, int Prefix);
	~EndpointServer();
	const char *GetAddress();
	int GetPort();
	int GetPrefix();
private:
	const char *address;
	int port;
	int prefix;
};

#endif 	// ENDPOINTSERVER_H