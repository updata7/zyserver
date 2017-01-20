#include "ServantMgr.h"

ServantMgr::ServantMgr()
{
	cout<<"ServantMgr init"<<endl;
}

void ServantMgr::InsertServant(string servant, class *T)
{
	servantList.insert(ServantList::value_type(servant, T));
}

void ServantMgr::RealseServant()
{
	ServantList::iterator it = servantList.begin();
	for (it; it != servantList.end(); it++)
	{
		DELETE it->second;
	}
}