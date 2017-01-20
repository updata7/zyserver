#ifndef COMMONCLASS_H
#define COMMONCLASS_H

#include "Memory.hpp"

#include <iostream>
using namespace std;

template <class T>
class CommonClass
{
public:
	CommonClass()
	{
		std::cout << "CommonClass init" << std::endl;
	}

	T* GetInstance()
	{
		m_pInstance = NEW T;
		return m_pInstance;
	}

	void DeleteInstance()
	{
		DELETE m_pInstance;
	}

private:
	T* m_pInstance;
};
#endif 	// COMMONCLASS_H