#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <string>
#include <iostream>
#include <list>

class MessageDispatch
{
public:
	MessageDispatch();
	~MessageDispatch();
	void Start();
private:
	static void DispatchMessage(void *userdata);
};

#endif 	// MESSAGEQUEUE_H