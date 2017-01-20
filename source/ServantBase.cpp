
#include "ServantBase.hpp"

ServantBase::ServantBase()
{
}


ServantBase::~ServantBase()
{
}

void ServantBase::Init()
{
	std::cout << "ServantBase Init" << std::endl;
}
void ServantBase::CallBack(std::string msg)
{
	std::cout << "ServantBase CallBack" << std::endl;
}