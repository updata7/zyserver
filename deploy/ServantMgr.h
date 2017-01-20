#ifndef SERVANT_MGR
#define SERVANT_MGR

#include <map>
#include <string>

using namespace std;

class ServantMgr
{
public:
	ServantMgr();
	void InsertServant(string servant, class *T);
	void RealseServant();

private:
	typedef std::map<string, class *> ServantList;
	ServantList servantList;
};

#endif 	// SERVANT_MGR