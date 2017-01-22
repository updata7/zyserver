
#include "Servant1.hpp"


Servant1::Servant1()
{
}


Servant1::~Servant1()
{
	std::cout << "Servant1 destory" << std::endl;
}

void Servant1::Init()
{
	std::cout << "Servant1 Init." << std::endl;
}

void Servant1::CallBack(std::string msg)
{
	std::cout << "Servant1 CallBack." << std::endl;
}
