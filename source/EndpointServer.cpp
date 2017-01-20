#include "EndpointServer.hpp"

EndpointServer::EndpointServer(const char *Address, int Port, int Prefix)
{
	address = Address;
	port = Port;
	prefix = Prefix;
}


EndpointServer::~EndpointServer()
{
}

const char *EndpointServer::GetAddress()
{
	return address;
}

int EndpointServer::GetPort()
{
	return port;
}

int EndpointServer::GetPrefix()
{
	return prefix;
}
