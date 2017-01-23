#ifndef TIMERMGR_H
#define TIMERMGR_H

class TimerMgr
{
public:
	TimerMgr();
	~TimerMgr();
	void Start();
private:
	static void *Execute(void *userdata);
};

#endif 	// TIMERMGR_H