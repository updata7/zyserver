
#include "Servant2.hpp"


Servant2::Servant2()
{
}


Servant2::~Servant2()
{
	std::cout << "Servant2 destory" << std::endl;
}

void Servant2::Init()
{
	std::cout << "Servant2 Init." << std::endl;
}

void Servant2::CallBack(std::string msg)
{
	std::cout << "Servant2 CallBack." << std::endl;
}
