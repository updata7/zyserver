#ifndef MASTERDBINFO_H
#define MASTERDBINFO_H

class MasterDbInfo
{
public:
	static int dbport;
	static char *dbhost;
	static char *dbuser;
	static char *dbpwd;
	static char *dbname;
	MasterDbInfo() {}
};

int MasterDbInfo::dbport = 0;
char *MasterDbInfo::dbhost = NULL;
char *MasterDbInfo::dbuser = NULL;
char *MasterDbInfo::dbpwd = NULL;
char *MasterDbInfo::dbname = NULL;

#endif 	// MASTERDBINFO_H